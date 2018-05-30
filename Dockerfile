FROM        ubuntu:16.04
MAINTAINER  Kerry Johnson <kerry.t.johnson@gmail.com>

ENV DEBIAN_FRONTEND=noninteractive                              \
    BAZEL_VERSION="0.13.0"                                      \
    BAZEL_INSTALLER="bazel-0.13.0-installer-linux-x86_64.sh"    \
    POCO_VERSION="1.9.0"                                        \
    BOOST_VERSION="1_67_0"

RUN apt-get --quiet         update              &&  \
    apt-get --quiet --yes   install g++             \
                                    git             \
                                    graphviz        \
                                    pkg-config      \
                                    python          \
                                    time			\
                                    tree			\
                                    unzip           \
                                    wget            \
                                    xdot            \
                                    zip             \
                                    zlib1g-dev
   
RUN mkdir -p /var/build/poco-build && cd /var/build/poco-build                                              &&  \
    wget --no-verbose "https://pocoproject.org/releases/poco-${POCO_VERSION}/poco-${POCO_VERSION}.tar.gz"   &&  \
    tar xzf poco-${POCO_VERSION}.tar.gz                                                                     &&  \
    cd /var/build/poco-build/poco-${POCO_VERSION}                                                           &&  \
    ./configure --minimal --no-tests --no-samples && make -j8

RUN mkdir -p /var/build/boost-build && cd /var/build/boost-build                                            &&  \
    wget --no-verbose "https://dl.bintray.com/boostorg/release/1.67.0/source/boost_${BOOST_VERSION}.tar.gz" &&  \
    tar xzf boost_${BOOST_VERSION}.tar.gz                                                                   &&  \
    cd /var/build/boost-build/boost_${BOOST_VERSION}                                                        &&  \
    ./bootstrap.sh                                                                                          &&  \
    ./b2

RUN  adduser    --shell /bin/bash       \
                --ingroup users         \
                --disabled-password     \
                --gecos 'Ubuntu user'   \
                --home /home/ubuntu     \
                ubuntu
                
USER ubuntu
WORKDIR /home/ubuntu

RUN mkdir -p ${HOME}/.bazel-install && cd ${HOME}/.bazel-install                                                    &&  \
    wget --no-verbose "https://github.com/bazelbuild/bazel/releases/download/${BAZEL_VERSION}/${BAZEL_INSTALLER}"   &&  \
    chmod +x "${BAZEL_INSTALLER}" && ./${BAZEL_INSTALLER} --user                                                    &&  \
    echo 'export PATH=${PATH}:${HOME}/bin' >> ${HOME}/.bashrc
    
RUN mkdir -p ${HOME}/projects/foss

CMD tail -f /dev/null
