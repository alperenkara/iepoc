#!/usr/bin/env python3


import os


def traverseDirectories():
    for folderName, subfolders, filenames in os.walk('C:/Users/alper/Documents/AGHP/GTSRB/Final_Training/Images/00000'):
        print('The current folder is ' + folderName)

        for subfolder in subfolders:
            print('SUBFOLDER OF ' + folderName + ': ' + subfolder)
        for filename in filenames:
            print('FILE INSIDE ' + folderName + ': ' + filename)

        print('')


from glob import glob
from os.path import expanduser, join

# Return everything under C:\Users\admin that contains a folder called wlp.
# glob('C:\\Users\\admin\\*\\wlp')

# Return everything under the user directory that contains a folder called wlp.
glob(join(expanduser('~'), '*', 'wlp'))


def collect_all_that_files(startPath, ext=".ppm"):
    all_file_list = os.listdir(startPath)
    file_list = [x for x in all_file_list if x.endswith(ext)]
    return file_list


# askdirectory(**options)

import tkinter as tk
import tkinter.filedialog as tkFDlg


def file_save():
    f = tkFileDialog.asksaveasfile(mode='w', defaultextension=".txt")
    if f is None:  # asksaveasfile return `None` if dialog closed with "cancel".
        return
        # text2save = str(text.get(1.0, END)) # starts from `1.0`, not `0.0`
        # f.write(text2save)
        # f.close() # `()` was missing.


def ask_4_directory():
    d = tkFDlg.askdirectory()
    return d


def find_all_files_that(path, ext=".ppm", min_size=0):
    """
        Returns a list of pairs:    file_name   file_size
        The returned files fulfil the conditions on the extension and minimal size
    """
    fileList = []
    try:

        fileList = [(os.path.join(dirpath, f))
                    for dirpath, dirnames, files in os.walk(path)
                    for f in files if f.endswith(ext) and os.path.getsize(os.path.join(dirpath, f)) >= min_size]

    except OSError as err:
        print(err)

    return fileList


# and os.path.getsize( f ) > 5000

if __name__ == "__main__":
    # startDir = "C:\\Temp\\HIL\\Source"
    startDir = ask_4_directory().replace('/', '\\')
    # alphaList = glob( startDir + "\\**\\*.cpp" )            # the magic \\**\\ means "go through all subdirectories" ==> nie dzia?a, podobno ma w Python 3.5
    # file_list = [ ( f, os.path.getsize( f ) ) for f in alphaList if os.path.getsize( f ) > 5000 ]
    # print( file_list )
    # big_file_list = [ f for f in file_list if f[1] > 5000 ]
    # print( big_file_list )
    good_list = find_all_files_that(startDir, ".ppm", 0)
    print(good_list)
    print ("\n")








