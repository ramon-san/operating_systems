# Disk reader

Disk reading tool for [HFS Plus](https://en.wikipedia.org/wiki/HFS_Plus) file system created with C. This repo contains different images in the `disk_reader/images/` directory, the image file system appears on its name. For example, `ntfs.img` indicates this image has a [NTFS](https://en.wikipedia.org/wiki/NTFS) file system. The program first reads the image's [MBR](https://en.wikipedia.org/wiki/master_boot_record), then it displays its partitions, and finally you can get more info on this partitions; when reading partitions the program only works with the HFS Plus file systems.

> Mac doesn't allow disks to boot through MBR, but it does allow files to be read through MBR. To do the actual booting you'd need to use [UUID](https://en.wikipedia.org/wiki/universally_unique_identifier) instead of MBR.

## Run the code

### Short way

Simply run `./run.sh` on the `disk_reader/` directory.

### Long way

To compile the code you just need to run the following command inside the `disk_reader/src/` directory:

``` Shell
make
```

Once you have the executable version run it with:

``` Shell
./disk_reader.exe ${FILE}
```

Here the `${FILE}` parameter represents the disk image you want to read. The src files are spread all over the place to follow a modular architecture and follow what I currently consider best practices. When running the code with `run.sh` a file called `disk_reader/images/hfs_plus.img` gets opened in the editor by default.

## Teacher instructions

Create a program capable of reading memory disks and retrieve information from their partitions if they use HFS Plus.

> All image files where provided by Dr. René Mac Kinney.
