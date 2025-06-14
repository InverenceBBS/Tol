# autoproxy.tcl - Copyright (C) 2002 Pat Thoyts <patthoyts@users.sf.net>
#
# On Unix the standard for identifying the local HTTP proxy server
# seems to be to use the environment variable http_proxy or ftp_proxy and
# no_proxy to list those domains to be excluded from proxying.
#
# On Windows we can retrieve the Internet Settings values from the registry
# to obtain pretty much the same information.
#
# With this information we can setup a suitable filter procedure for the 
# Tcl http package and arrange for automatic use of the proxy.
#
# Example:
#   package require autoproxy
#   autoproxy::init
#   set tok [http::geturl http://wiki.tcl.tk/]
#   http::data $tok
#
# To support https add:
#   package require tls
#   http::register https 443 ::autoproxy::tls_socket
#
# @(#)$Id: autoproxy.tcl,v 1.9 2007/03/12 22:53:25 patthoyts Exp $

package require http;                   # tcl
package require uri;                    # tcllib
package require base64;                 # tcllib

namespace eval ::autoproxy {
    variable rcsid {$Id: autoproxy.tcl,v 1.9 2007/03/12 22:53:25 patthoyts Exp $}
    variable version 1.4
    variable options

    if {! [info exists options]} {
        array set options {
            proxy_host ""
            proxy_port 80
            no_proxy   {}
            basic      {} 
            authProc   {}
        }
    }

    variable winregkey
    set winregkey [join {
        HKEY_CURRENT_USER
        Software Microsoft Windows
        CurrentVersion "Internet Settings"
    } \\]
}

# -------------------------------------------------------------------------
# Description:
#   Obtain configuration options for the server.
#
proc ::autoproxy::cget {option} {
    variable options
    switch -glob -- $option] {
        -host -
        -proxy_h* { set options(proxy_host) }
        -port -
        -proxy_p* { set options(proxy_port) }
        -no*      { set options(no_proxy) }
        -basic    { set options(basic) }
        -authProc { set options(authProc) }
        default {
            set err [join [lsort [array names options]] ", -"]
            return -code error "bad option \"$option\":\
                       must be one of -$err"
        }
    }
}

# -------------------------------------------------------------------------
# Description:
#  Configure the autoproxy package settings.
#  You may only configure one type of authorisation at a time as once we hit
#  -basic, -digest or -ntlm - all further args are passed to the protocol
#  specific script.
#
#  Of course, most of the point of this package is to fill as many of these
#  fields as possible automatically. You should call autoproxy::init to
#  do automatic configuration and then call this method to refine the details.
#
proc ::autoproxy::configure {args} {
    variable options

    if {[llength $args] == 0} {
        foreach {opt value} [array get options] {
            lappend r -$opt $value
        }
        return $r
    }

    while {[string match "-*" [set option [lindex $args 0]]]} {
        switch -glob -- $option {
            -host - 
            -proxy_h* { set options(proxy_host) [Pop args 1]}
            -port - 
            -proxy_p* { set options(proxy_port) [Pop args 1]}
            -no*      { set options(no_proxy) [Pop args 1] }
            -basic    { Pop args; configure:basic $args ; break }
            -authProc { set options(authProc) [Pop args] }
            --        { Pop args; break }
            default {
                set opts [join [lsort [array names options]] ", -"]
                return -code error "bad option \"$option\":\
                       must be one of -$opts"
            }
        }
        Pop args
    }
}

# -------------------------------------------------------------------------
# Description:
#  Initialise the http proxy information from the environment or the
#  registry (Win32)
#
#  This procedure will load the http package and re-writes the
#  http::geturl method to add in the authorisation header.
#
#  A better solution will be to arrange for the http package to request the
#  authorisation key on receiving an authorisation reqest.
#
proc ::autoproxy::init {{httpproxy {}} {no_proxy {}}} {
    global tcl_platform
    global env
    variable winregkey
    variable options

    # Look for standard environment variables.
    if {[string length $httpproxy] > 0} {
        
        # nothing to do

    } elseif {[info exists env(http_proxy)]} {
        set httpproxy $env(http_proxy)
        if {[info exists env(no_proxy)]} {
            set no_proxy $env(no_proxy)
        }
    } else {
        if {$tcl_platform(platform) == "windows"} {
            package require registry 1.0
            array set reg {ProxyEnable 0 ProxyServer "" ProxyOverride {}}
            catch {
                # IE5 changed ProxyEnable from a binary to a dword value.
                switch -exact -- [registry type $winregkey "ProxyEnable"] {
                    dword {
                        set reg(ProxyEnable) [registry get $winregkey "ProxyEnable"]
                    }
                    binary {
                        set v [registry get $winregkey "ProxyEnable"]
                        binary scan $v i reg(ProxyEnable)
                    }
                    default { 
                        return -code error "unexpected type found for\
                               ProxyEnable registry item"
                    }
                }
                set reg(ProxyServer) [GetWin32Proxy http]
                set reg(ProxyOverride) [registry get $winregkey "ProxyOverride"]
            }
            if {![string is bool $reg(ProxyEnable)]} {
                set reg(ProxyEnable) 0
            }
            if {$reg(ProxyEnable)} {
                set httpproxy $reg(ProxyServer)
                set no_proxy  $reg(ProxyOverride)
            }
        }
    }
    
    # If we found something ...
    if {[string length $httpproxy] > 0} {
        # The http_proxy is supposed to be a URL - lets make sure.
        if {![regexp {\w://.*} $httpproxy]} {
            set httpproxy "http://$httpproxy"
        }
        
        # decompose the string.
        array set proxy [uri::split $httpproxy]

        # turn the no_proxy value into a tcl list
        set no_proxy [string map {; " " , " "} $no_proxy]

        # configure ourselves
        configure -proxy_host $proxy(host) \
            -proxy_port $proxy(port) \
            -no_proxy $no_proxy

        # Lift the authentication details from the environment if present.
        if {[string length $proxy(user)] < 1 \
                && [info exists env(http_proxy_user)] \
                && [info exists env(http_proxy_pass)]} {
            set proxy(user) $env(http_proxy_user)
            set proxy(pwd)  $env(http_proxy_pass)
        }

        # Maybe the proxy url has authentication parameters?
        # At this time, only Basic is supported.
        if {[string length $proxy(user)] > 0} {
            configure -basic -username $proxy(user) -password $proxy(pwd)
        }

        # setup and configure the http package to use our proxy info.
        http::config -proxyfilter [namespace origin filter]
    }
    return $httpproxy
}

# autoproxy::GetWin32Proxy -- 
#
#	Parse the Windows Internet Settings registry key and return the
#	protocol proxy requested. If the same proxy is in use for all 
#	protocols, then that will be returned. Otherwise the string is
#	parsed. Example:
#	 ftp=proxy:80;http=proxy:80;https=proxy:80
#
proc ::autoproxy::GetWin32Proxy {protocol} {
    variable winregkey
    set proxies [split [registry get $winregkey "ProxyServer"] ";"]
    foreach proxy $proxies {
        if {[string first = $proxy] == -1} {
            return $proxy
        } else {
            foreach {prot host} [split $proxy =] break
            if {[string compare $protocol $prot] == 0} {
                return $host
            }
        }
    }
    return -code error "failed to identify an '$protocol' proxy"
}

# -------------------------------------------------------------------------
# Description:
#  Pop the nth element off a list. Used in options processing.
proc ::autoproxy::Pop {varname {nth 0}} {
    upvar $varname args
    set r [lindex $args $nth]
    set args [lreplace $args $nth $nth]
    return $r
}

# -------------------------------------------------------------------------
# Description
#   An example user authentication procedure.
# Returns:
#   A two element list consisting of the users authentication id and 
#   password. 
proc ::autoproxy::defAuthProc {{user {}} {passwd {}} {realm {}}} {
    if {[string length $realm] > 0} {
        set title "Realm: $realm"
    } else {
        set title {}
    }

    # If you are using BWidgets then the following will do:
    #
    #    package require BWidget
    #    return [PasswdDlg .defAuthDlg -parent {} -transient 0 \
    #         -title $title -logintext $user -passwdtext $passwd]
    #
    # if you just have Tk and no BWidgets --
    
    set dlg [toplevel .autoproxy_defAuthProc -class Dialog]
    wm title $dlg "$realm"
    label $dlg.ll -text Login -underline 0 -anchor w
    entry $dlg.le -textvariable [namespace current]::${dlg}:l
    label $dlg.pl -text Password -underline 0 -anchor w
    entry $dlg.pe -show * -textvariable [namespace current]::${dlg}:p
    button $dlg.ok -text OK -default active -width -11 \
        -command [list set [namespace current]::${dlg}:ok 1]
    grid $dlg.ll $dlg.le -sticky news
    grid $dlg.pl $dlg.pe -sticky news
    grid $dlg.ok - -sticky e
    grid columnconfigure $dlg 1 -weight 1
    bind $dlg <Return> [list $dlg.ok invoke]
    bind $dlg <Alt-l> [list focus $dlg.le]
    bind $dlg <Alt-p> [list focus $dlg.pe]
    variable ${dlg}:l $user; variable ${dlg}:p $passwd
    variable ${dlg}:ok 0
    wm deiconify $dlg; focus $dlg.pe; update idletasks
    set old [::grab current]; grab $dlg
    tkwait variable [namespace current]::${dlg}:ok
    grab release $dlg ; if {[llength $old] > 0} {::grab $old}
    set r [list [set ${dlg}:l] [set ${dlg}:p]]
    unset ${dlg}:l; unset ${dlg}:p; unset ${dlg}:ok
    destroy $dlg
    return $r
}

# -------------------------------------------------------------------------

# Description:
#  Implement support for the Basic authentication scheme (RFC 1945,2617).
# Options:
#  -user userid  - pass in the user ID (May require Windows NT domain
#                  as DOMAIN\\username)
#  -password pwd - pass in the user's password.
#  -realm realm  - pass in the http realm.
#
proc ::autoproxy::configure:basic {arglist} {
    variable options
    array set opts {user {} passwd {} realm {}}
    foreach {opt value} $arglist {
        switch -glob -- $opt {
            -u* { set opts(user) $value}
            -p* { set opts(passwd) $value}
            -r* { set opts(realm) $value}
            default {
                return -code error "invalid option \"$opt\": must be one of\
                     -username or -password or -realm"
            }
        }
    }

    # If nothing was provided, try calling the authProc
    if {$options(authProc) != {} \
            && ($opts(user) == {} || $opts(passwd) == {})} {
        set r [$options(authProc) $opts(user) $opts(passwd) $opts(realm)]
        set opts(user) [lindex $r 0]
        set opts(passwd) [lindex $r 1]
    }

    # Store the encoded string to avoid re-encoding all the time.
    set options(basic) [list "Proxy-Authorization" \
                            [concat "Basic" \
                                 [base64::encode $opts(user):$opts(passwd)]]]
    return
}

# -------------------------------------------------------------------------
# Description:
#  An http package proxy filter. This attempts to work out if a request
#  should go via the configured proxy using a glob comparison against the
#  no_proxy list items. A typical no_proxy list might be
#   [list localhost *.my.domain.com 127.0.0.1]
#
#  If we are going to use the proxy - then insert the proxy authorization
#  header.
#
proc ::autoproxy::filter {host} {
    variable options

    if {$options(proxy_host) == {}} {
        return {}
    }
    
    foreach domain $options(no_proxy) {
        if {[string match $domain $host]} {
            return {}
        }
    }
    
    # Add authorisation header to the request (by Anders Ramdahl)
    catch {
        upvar state State
        if {$options(basic) != {}} {
            set State(-headers) [concat $options(basic) $State(-headers)]
        }
    }
    return [list $options(proxy_host) $options(proxy_port)]
}

# autoproxy::tls_connect --
#
#	Create a connection to a remote machine through a proxy
#	if necessary. This is used by the tls_socket comment for 
#	use with the http package but can also be used more generally
#	provided your proxy will permit CONNECT attempts to ports
#	other than port 443 (many will not).
#
proc ::autoproxy::tls_connect {host port {useragent {}}} {
    variable options
    if {[string length $options(proxy_host)] > 0} {
        set s [::socket $options(proxy_host) $options(proxy_port)]
        fconfigure $s -blocking 1 -buffering line -translation crlf
        puts $s "CONNECT $host:$port HTTP/1.1"
        puts $s "Host: $host"
        if {[string length $useragent] > 0} {
            puts $s "User-Agent: $useragent"
        }
        puts $s "Proxy-Connection: keep-alive"
        puts $s "Connection: keep-alive"
        if {[string length $options(basic)] > 0} {
            puts $s [join $options(basic) ": "]
        }
        puts $s ""

        set block ""
        while {[gets $s r] > 0} {
            lappend block $r
        }
        set result [lindex $block 0]
        set code [lindex [split $result { }] 1]

        if {$code >= 200 && $code < 300} {
            fconfigure $s -blocking 1 -buffering none -translation binary
            tls::import $s
        } else {
            close $s
            return -code error $result
        }
    } else {
        set s [eval [linsert $args 0 ::tls::socket]]
    }
    return $s
}

# autoproxy::tls_socket --
#
#	This can be used to handle TLS connections indenpendantly of
#	proxy presence. It can only be used with the Tcl http package
#	and to use it you must do:
#	   http::register https 443 ::autoproxy::tls_socket
#	After that you can use the http::geturl command to access
#	secure web pages and any proxy details will be handled for you.
#
proc ::autoproxy::tls_socket {args} {
    variable options

    # Look into the http package for the actual target. The function
    # has unfortunately not passed these as parameters.
    upvar host host port port
    set s [tls_connect $host $port [http::config -useragent]]

    # record the tls connection status in the http state array.
    upvar state state
    tls::handshake $s
    set state(tls_status) [tls::status $s]

    return $s
}

# -------------------------------------------------------------------------

package provide autoproxy $::autoproxy::version

# -------------------------------------------------------------------------
#
# Local variables:
#   mode: tcl
#   indent-tabs-mode: nil
# End:
