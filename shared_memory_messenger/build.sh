#!/bin/sh

make clean -C src/
docker image build --tag shm_example .
docker container run -it --rm shm_example
docker rmi shm_example