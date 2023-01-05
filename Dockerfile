# FIXME: fix linker errors

# Command to build docker: docker build -t logwin-app .

# Use alpine base image
FROM alpine:3.14

# Install required packages via apk
RUN apk update
RUN apk add git cmake ninja gcc g++ make libexecinfo-dev

# Make gclados executable and libgclados.a
RUN git clone https://github.com/AlexShukel/gclados.git
WORKDIR /gclados
RUN cmake -B cmake-build-release -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" -S .
RUN cmake --build cmake-build-release
RUN cd bin && ls
RUN cp ./bin/gclados /bin/gclados

# Copy project files
COPY . /app
RUN cp ./bin/libgclados.a /app/lib/libgclados.a

# Make libargon2.a
WORKDIR /app/external/phc-winner-argon2
RUN make
RUN cp ./libargon2.a ../../lib/libargon2.a

WORKDIR /app

# Create cmake configuration
RUN cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc -B cmake-build-release -G Ninja
# Build project
RUN cmake --build cmake-build-release

# Run tests
RUN cd ./cmake-build-release && ctest
