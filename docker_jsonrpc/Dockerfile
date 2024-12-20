# Use the official GCC base image
FROM gcc:latest

# Set working directory
WORKDIR /usr/src/app

# Install required libraries and git
RUN apt-get update && \
    apt-get install -y \
    libjsoncpp-dev \
    g++ \
    make \
    curl \
    git \
    && rm -rf /var/lib/apt/lists/*

# Clone the cpp-httplib repository
RUN git clone https://github.com/yhirose/cpp-httplib.git && \
    mv cpp-httplib/httplib.h /usr/include/ && \
    rm -rf cpp-httplib

# Copy the C++ source code into the container
COPY docker_pub.cpp .

# Compile the C++ program
RUN g++ -o docker_pub docker_pub.cpp -ljsoncpp -lpthread -I/usr/include/jsoncpp

# Expose the port where the server will run
EXPOSE 8080

# Run the program
CMD ["./docker_pub"]
