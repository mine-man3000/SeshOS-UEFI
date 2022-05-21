#!/usr/bin/env python3
from datetime import date
import time
import os
import sys

import cv2

if len(sys.argv) < 3:
    print("Usage: icontest.py <bitmapfile> <output_name>")
    raise TypeError("Usage: icontest.py <bitmapfile> <output_name>")

# Arguments variables
IMAGE_FILEPATH = sys.argv[1]
HEADER_FILEPATH = sys.argv[2]

if HEADER_FILEPATH[-1] != "h":
    raise TypeError("OUTPUT FILE IS NOT A .h FILE!")

IMAGE_HEADER_FILENAME = HEADER_FILEPATH.split("/")[-1].split(".")[0]

# The current time
DATE_RIGHT_FORMAT = str(date.today()).split("-")
NEW_TODAY = "/".join([DATE_RIGHT_FORMAT[1], DATE_RIGHT_FORMAT[2], DATE_RIGHT_FORMAT[0]])
MOD_DATE = time.ctime(os.path.getmtime(IMAGE_FILEPATH)).split(" ")
FINAL_MOD_DATE = "/".join([MOD_DATE[1], MOD_DATE[2], MOD_DATE[4]])

# Read the image file
IMAGE = cv2.imread(IMAGE_FILEPATH, cv2.IMREAD_UNCHANGED)
WIDTH = IMAGE.shape[1]
HEIGHT = IMAGE.shape[0]

with open(HEADER_FILEPATH, "w", encoding="utf-8") as f:
    f.write("/*****************************************  \n")
    f.write("                   SeshOS                   \n")
    f.write("                                          \n\n")
    f.write("  This is a converted icon to embed into    \n")
    f.write("            the kernel image.               \n")
    f.write(" * Converted File: ")
    f.write(IMAGE_FILEPATH)
    f.write("                                            \n")
    f.write(" * Converted Date: ")
    f.write(NEW_TODAY)
    f.write("                                            \n")
    f.write(" * Icon Last Mod: ")
    f.write(FINAL_MOD_DATE)
    f.write("                                            \n")
    f.write("*****************************************/\n\n")
    f.write('#include "../video/video.h"\n')
    f.write(f"uint32_t g_{IMAGE_HEADER_FILENAME}_data[] = {{\n")

    for y in range(HEIGHT):
        f.write("\t")
        for x in range(WIDTH):

            PIXEL = IMAGE[y, x]
            RGB = 0

            RGB |= PIXEL[0] << 0  # blue
            RGB |= PIXEL[1] << 8  # green
            RGB |= PIXEL[2] << 16  # red

            RGB_HEX = hex(RGB).split("x")
            NEW_RGBA_HEX = f"0x00{RGB_HEX[1]}, "

            if NEW_RGBA_HEX == "0x000, ":
                NEW_RGBA_HEX = "0x00000000, "
            f.write(NEW_RGBA_HEX)
        f.write("'2',\n")

    f.write("3};\n\n")
    f.write(f"Image g_{IMAGE_HEADER_FILENAME}_icon = {{\n")
    f.write(f"\t{WIDTH}, {HEIGHT}, g_{IMAGE_HEADER_FILENAME}_data\n")
    f.write("};\n")
