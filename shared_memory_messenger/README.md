# Shared Memory Messenger

A quick implementation of a messenger applied through shared memory objects.

## Building your environment

### Short way

It's recommended to run the code on its dedicated development environment, to build this environment start your Docker daemon (just start Docker) and run this script on the `shared_memory_messenger/` directory:

``` Shell
./build.sh
```

### Long way

You could also run the following commands inside the `shared_memory_messenger/` directory and start your container manually, this is exactly what the `build.sh` script does:

``` Shell
docker image build --tag shm_example .
docker container run -it --rm shm_example
```

When you no longer want the image remove it with:

``` Shell
docker rmi shm_example
```

## Run the code

### Short way

Simply run `./run.sh` on the `shared_memory_messenger/` directory.

### Long way

To compile the code you just need to run the following command inside the `shared_memory_messenger/src/` directory:

``` Shell
make
```

Once you have the executable version run it with:

``` Shell
./messenger.exe ${BUFFER_SIZE}
```

Here the `${BUFFER_SIZE}` parameter represents the maximum size any given message can have. The src files are spread all over the place to follow a modular architecture and follow what I currently consider best practices. When running the code from `run.sh` buffer size is set to 64 Bytes by default.

## Teacher instructions

A small message service should be done using shared memory using shared memory objects.

- The name of the object is the conversation.
- The program should ask whether to read or write a message (or you can have a program for each thing).
- You must keep track of the messages read (which free memory) and
messages left (consuming memory).
- To access shared memory, semaphores must be used.