FROM jenkins/ssh-agent:jdk11
RUN apt-get update
RUN apt-get install -y python3 python3-pip gfortran build-essential libhdf5-serial-dev pkg-config libopenmpi-dev openmpi-bin
RUN pip3 install numpy matplotlib h5py scipy
COPY Makefile.h /home/jenkins