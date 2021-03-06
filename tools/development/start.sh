#!/bin/bash

################################################################################################################################################################

# @project        Library ▸ Physics
# @file           tools/development/start.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

set -a
set -e

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
tools_directory="${script_directory}/.."

################################################################################################################################################################

# Setup environment

source "${tools_directory}/.env"

################################################################################################################################################################

# Build Docker image if it does not exist already

pull_image ()
{

    echo "Pulling Docker image [${image_repository}:${image_tag}]..."

    {
        docker pull "${image_repository}:${image_tag}" 2> /dev/null && pull_result=1
    } || {
        echo "Cannot pull Docker image [${image_repository}:${image_tag}]." && pull_result=0
    }

}

build_image ()
{

    echo "Building Docker image [${image_repository}:${image_tag}]..."

    pushd "${script_directory}/docker" > /dev/null

    ./build.sh

    popd > /dev/null

}

pull_or_build_image ()
{

    if [[ "$(docker images -q ${image_repository}:${image_tag} 2> /dev/null)" == "" ]]; then

        pull_image

        if [[ ${pull_result} -eq 0 ]]; then
            build_image
        fi

    fi

}

################################################################################################################################################################

# Run Docker container

run_container ()
{

    options=""
    command="/bin/bash"

    # Setup linked mode

    if [[ ! -z $1 ]] && [[ $1 == "--link" ]]; then

        options=""
        command=""

        # Library ▸ Core

        if [[ ! -d ${library_core_directory} ]]
        then

            echo "Library ▸ Core directory [${library_core_directory}] cannot be found."

            exit 1

        fi

        options="${options} \
        --volume=${library_core_directory}:/mnt/library-core:ro,delegated"

        command=" \
        rm -rf /usr/local/include/Library/Core; \
        rm -f /usr/local/lib/liblibrary-core.so*; \
        cp -as /mnt/library-core/include/Library/Core /usr/local/include/Library/Core; \
        cp -as /mnt/library-core/src/Library/Core/* /usr/local/include/Library/Core/; \
        ln -s /mnt/library-core/lib/liblibrary-core.so /usr/local/lib/; \
        ln -s /mnt/library-core/lib/liblibrary-core.so.0 /usr/local/lib/;"

        # Library ▸ I/O

        if [[ ! -d ${library_io_directory} ]]
        then

            echo "Library ▸ I/O directory [${library_io_directory}] cannot be found."

            exit 1

        fi

        options="${options} \
        --volume=${library_io_directory}:/mnt/library-io:ro,delegated"

        command="${command} \
        rm -rf /usr/local/include/Library/IO; \
        rm -f /usr/local/lib/liblibrary-io.so*; \
        cp -as /mnt/library-io/include/Library/IO /usr/local/include/Library/IO; \
        cp -as /mnt/library-io/src/Library/IO/* /usr/local/include/Library/IO/; \
        ln -s /mnt/library-io/lib/liblibrary-io.so /usr/local/lib/; \
        ln -s /mnt/library-io/lib/liblibrary-io.so.0 /usr/local/lib/;"

        ## Library ▸ Mathematics

        if [[ ! -d ${library_mathematics_directory} ]]
        then

            echo "Library ▸ Mathematics directory [${library_mathematics_directory}] cannot be found."

            exit 1

        fi

        options="${options} \
        --volume=${library_mathematics_directory}:/mnt/library-mathematics:ro,delegated"

        command="${command} \
        rm -rf /usr/local/include/Library/Mathematics; \
        rm -f /usr/local/lib/liblibrary-mathematics.so*; \
        cp -as /mnt/library-mathematics/include/Library/Mathematics /usr/local/include/Library/Mathematics; \
        cp -as /mnt/library-mathematics/src/Library/Mathematics/* /usr/local/include/Library/Mathematics/; \
        ln -s /mnt/library-mathematics/lib/liblibrary-mathematics.so /usr/local/lib/; \
        ln -s /mnt/library-mathematics/lib/liblibrary-mathematics.so.0 /usr/local/lib/;"

        # Output

        command="${command} \
        /bin/bash"

    fi

    docker run \
    --name=${container_name} \
    -it \
    --rm \
    --privileged \
    ${options} \
    --env-file="${script_directory}/.env" \
    --volume="${project_directory}:/app:rw,delegated" \
    --volume="${script_directory}/helpers/build.sh:/app/build/build.sh:ro,delegated" \
    --volume="${script_directory}/helpers/test.sh:/app/build/test.sh:ro,delegated" \
    --volume="${script_directory}/helpers/debug.sh:/app/build/debug.sh:ro,delegated" \
    --volume="${script_directory}/helpers/clean.sh:/app/build/clean.sh:ro,delegated" \
    --workdir="/app/build" \
    ${image_repository}:${image_tag} \
    /bin/bash -c "${command}"

}

################################################################################################################################################################

pull_or_build_image
run_container

################################################################################################################################################################
