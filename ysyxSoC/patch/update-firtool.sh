#!/usr/bin/env bash
set -eu

# Usage:
#   replace_firtool <firtool_url> <firtool_sha256_url> <firtool_update_version>
replace_firtool() {
    local firtool_url=$1
    local firtool_sha256_url=$2
    local firtool_update_version=$3
    local firtool_patch_dir=$4

    # Check if firtool directory exists
    if [ -d $firtool_patch_dir ]; then
        echo "Found existing firtool directory in $firtool_patch_dir"
        echo "If you want to update firtool, please remove the existing firtool directory"
        exit 0
    fi

    # Create temporary directory
    local firtool_temp=$(mktemp -d)
    echo "Downloading firtool version $firtool_update_version from $firtool_url..."
    curl -L -o $firtool_temp/firtool.tar.gz $firtool_url
    echo "Downloading SHA256 checksum from $firtool_sha256_url..."
    # Check SHA256 checksum
    check_sha256=$(curl -L $firtool_sha256_url)
    echo "Checking SHA256 checksum..."
    echo "$check_sha256 $firtool_temp/firtool.tar.gz" | sha256sum -c -

    if [ $? -ne 0 ]; then
        echo "SHA256 checksum failed"
        exit 1
    fi

    # Extract firtool to patch directory
    mkdir -p $firtool_patch_dir
    tar -xzf $firtool_temp/firtool.tar.gz -C $firtool_patch_dir
    chmod +x $firtool_patch_dir/firtool-$firtool_update_version/bin/firtool
}

update_firtool() {
    local firtool_update_version=$1
    local firtool_patch_dir=$2

    case "$(uname -s)" in
        Linux*) firtool_arch="linux-x64";;
        Darwin*)
            if [ "$(uname -m)" == "arm64" ]; then
                # CIRCT does not release darwin arm64 binary yet
                # so we need to build it from source
                echo "Unsupported darwin architecture"
                echo "Please build firtool from source, see: https://github.com/llvm/circt?tab=readme-ov-file#setting-this-up"
                echo "Then copy the built firtool binary to $firtool_patch_dir/firtool-$firtool_update_version/bin/firtool"
                exit 1
            else
                firtool_arch="macos-x64"
            fi
            ;;
        *) echo "Unsupported OS"; exit 1;;
    esac

    local firtool_url="https://github.com/llvm/circt/releases/download/firtool-${firtool_update_version}/firrtl-bin-${firtool_arch}.tar.gz"
    local firtool_sha256="https://github.com/llvm/circt/releases/download/firtool-${firtool_update_version}/firrtl-bin-${firtool_arch}.tar.gz.sha256"

    case "$(uname -s)" in
        Linux*) replace_firtool $firtool_url $firtool_sha256 $firtool_update_version $firtool_patch_dir;;
        Darwin*) replace_firtool $firtool_url $firtool_sha256 $firtool_update_version $firtool_patch_dir;;
        *) echo "Unsupported OS"; exit 1;;
    esac
}

# Call update_firtool with version and patch directory
# e.g. update_firtool 1.105.0 `pwd`/patch/firtool
update_firtool $1 $2