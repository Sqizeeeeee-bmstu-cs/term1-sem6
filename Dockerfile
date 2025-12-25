FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    clang \
    cmake \
    && rm -rf /var/lib/apt/lists/*


WORKDIR /app

COPY . /app

RUN mkdir build && cd build \
    && cmake .. \
    && make

CMD ["./build/tasks"]

