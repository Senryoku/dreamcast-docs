        ��  ��                  (
      �� ��     0 	                 4         L         �  2   2   �     [OK]
     [ERR]
 P   
 Listing %1
 New files added to this directory will be compressed.

   T   
 Listing %1
 New files added to this directory will not be compressed.

   �   
Of %1 files within %2 directories
%3 are compressed and %4 are not compressed.
%5 total bytes of data are stored in %6 bytes.
The compression ratio is %7 to 1.

    @   
 Setting the directory %1 to compress new files %0

    $   
 Compressing files in %1

  $   
 Compressing files in %1

  �   
%1 files within %2 directories were compressed.
%3 total bytes of data are stored in %4 bytes.
The compression ratio is %5 to 1.
  D   
 Setting the directory %1 not to compress new files %0

    (   
 Uncompressing files in %1

    (   
 Uncompressing files in %1

    <   
%1 files within %2 directories were uncompressed.

    Out of memory.
       [Skipping %1]
    %1%0
     %1
    8   %1: The file system does not support compression.
    to 1 %0
   (   Invalid drive specification: %1
   x   %1: The file system does not support compression or
the cluster size of the volume is larger than 4096 bytes.
    x  Displays or alters the compression of files on NTFS partitions.

COMPACT [/C | /U] [/S[:dir]] [/A] [/I] [/F] [/Q] [filename [...]]

  /C        Compresses the specified files.  Directories will be marked
            so that files added afterward will be compressed.
  /U        Uncompresses the specified files.  Directories will be marked
            so that files added afterward will not be compressed.
  /S        Performs the specified operation on files in the given
            directory and all subdirectories.  Default "dir" is the
            current directory.
  /A        Displays files with the hidden or system attributes.  These
            files are omitted by default.
  /I        Continues performing the specified operation even after errors
            have occurred.  By default, COMPACT stops when an error is
            encountered.
  /F        Forces the compress operation on all specified files, even
            those which are already compressed.  Already-compressed files
            are skipped by default.
  /Q        Reports only the most essential information.
  filename  Specifies a pattern, file, or directory.

  Used without parameters, COMPACT displays the compression state of
  the current directory and any files it contains. You may use multiple
  filenames and wildcards.  You must put spaces between multiple
  parameters.
 