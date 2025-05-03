FROM ubuntu:24.04

# Avoid prompts during package installation
ARG DEBIAN_FRONTEND=noninteractive

# Install essential build tools and dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libeigen3-dev \
    libgtest-dev \
    nlohmann-json3-dev \
    doxygen \
    graphviz \
    clang \
    clang-format \
    clang-tidy \
    clangd \
    lld \
    lldb \
    valgrind \
    gdb \
    wget \
    curl \
    pkg-config \
    python3 \
    python3-pip \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Set up alternative compiler options
RUN update-alternatives --install /usr/bin/cc cc /usr/bin/clang 100 \
    && update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++ 100

# Create a non-root user for development
ARG USERNAME=dev
ARG USER_UID=1001
ARG USER_GID=1001

RUN apt-get update && apt-get install -y sudo \
    && groupadd --gid $USER_GID $USERNAME \
    && useradd -s /bin/bash --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Set up default compiler flags for C++17
ENV CXXFLAGS="-std=c++17 -Wall -Wextra -Wpedantic"

# Set up working directory
WORKDIR /workspace

# Switch to non-root user
USER $USERNAME

CMD ["/bin/bash"]
