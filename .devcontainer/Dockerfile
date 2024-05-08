FROM mcr.microsoft.com/devcontainers/base:ubuntu

# Update and install all dependencies
RUN apt-get update && apt-get install -y \
    xz-utils \
    gcc \
    clang \
    git-all \
    git-core \
    sudo \
    build-essential \
    cmake \
    valgrind \
    libcppunit-dev \
    zsh \
    curl \
    libreadline-dev \
    python3-pip \
    python-dev-is-python3 \
    python3.10-venv

RUN apt install -y cppcheck clang-tidy

# Upgrade pip and setuptools, and install norminette
RUN python3 -m pip install --upgrade pip setuptools && \
    python3 -m pip install norminette

# instal minishell tester
RUN curl -fsSL -o install.sh https://raw.githubusercontent.com/zstenger93/42_minishell_tester/master/install.sh
RUN bash install.sh