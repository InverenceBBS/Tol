import os
from pathlib import Path

# Directory containing this script
ROOT = Path(__file__).resolve().parents[1]
TOL_MASTER = ROOT / "tol-master"

# Build script file names we want to collect
BUILD_SCRIPT_NAMES = {
    "CMakeLists.txt",
    "configure",
    "configure.ac",
    "configure.in",
    "Makefile.am",
    "Makefile.in",
    "aclocal.m4",
    "Jamfile",
    "Jamroot",
}

# Windows-specific directories to exclude
WINDOWS_DIRS = {
    "windows",
    "win-vc8",
    "win-vc9",
    "win-VC8",
    "win-VC9",
}

def is_build_script(path: Path) -> bool:
    return path.name in BUILD_SCRIPT_NAMES


def should_keep_directory(path: Path) -> bool:
    """Return True if the directory should be retained."""
    parts = path.parts
    if not parts:
        return False

    # Exclude Windows-specific packaging directories anywhere in the path
    if any(part in WINDOWS_DIRS for part in parts):
        return False

    # Keep only the top-level core implementation directories
    if parts[0] in {"tol", "tolbase", "tolbaseBLT"}:
        return len(parts) == 1

    return False


def main():
    keep_files = []
    keep_dirs = []

    for dirpath, dirnames, filenames in os.walk(TOL_MASTER):
        p = Path(dirpath)
        if should_keep_directory(p.relative_to(TOL_MASTER)):
            keep_dirs.append(p.relative_to(ROOT))
        # Remove Windows directories from search
        dirnames[:] = [d for d in dirnames if d not in WINDOWS_DIRS]

        for filename in filenames:
            fpath = p / filename
            if is_build_script(fpath):
                keep_files.append(fpath.relative_to(ROOT))

    print("Directories to keep:")
    for d in sorted(set(keep_dirs)):
        print(d)
    print("\nBuild scripts to keep:")
    for f in sorted(set(keep_files)):
        print(f)


if __name__ == "__main__":
    main()
