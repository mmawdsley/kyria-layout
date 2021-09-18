#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from argparse import ArgumentParser
from PIL import Image
import pathlib

class OledConverter(object):
    """Converts a bitmap file to raw bytes."""

    def __init__(self, image):
        """Check the image has the correct height."""
        self.image = image
        self.width, self.height = self.image.size

        if self.height % 8 != 0:
            raise Exception("Image height is not a multiple of 8")

    def convert(self):
        """Convert the bitmap to raw bytes."""

        pixels = self.image.load()
        data = []

        # Each byte is an 8 pixel wide column, moving from the top left so we
        # need to split the height into 8 pixel tall chunks
        for y in range(0, int(self.height / 8)):
            for x in range(0, self.width):
                byte = 0

                # Check the block from the bottom so the lowest pixel has the
                # highest value in the byte
                for z in reversed(range(0, 8)):
                    pixel = pixels[x, y * 8 + z]
                    byte = byte << 1

                    if pixel > 128:
                        byte = byte | 1

                data.append(byte)

        return data

if __name__ == "__main__":
    parser = ArgumentParser()
    parser.add_argument('image', help='filename', type=pathlib.Path)
    args = parser.parse_args()

    with Image.open(args.image) as image:
        data = OledConverter(image).convert()
        x = 0

        for bit in data:
            print('0x{0:0{1}x}, '.format(bit, 2), end="")
            x += 1

            if x % 16 == 0:
                print("")
