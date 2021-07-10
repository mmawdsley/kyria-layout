#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from PIL import Image, ImageDraw, ImageFont
from keycodes import KEYCODES
from argparse import ArgumentParser
import json
import sys

KEY_WIDTH = 50
NUM_COLS = 16
NUM_ROWS = 4
KEYBOARD_GUTTER = 10
TITLE_GUTTER = 80
IMAGE_PADDING = 10
KEY_GUTTER = 5
BOTTOM_OFFSET = 30
GAP = 100
BIG_GAP = GAP + 4 * (KEY_WIDTH + KEY_GUTTER)
ROW_INDENT = round((KEY_WIDTH + KEY_GUTTER) * 2.4)
ROW_OFFSET = KEY_WIDTH + KEY_GUTTER
BOTTOM_GAP = 216
TTF_FONT_PATH = '/usr/share/fonts/truetype/ttf-bitstream-vera/Vera.ttf'
FONT_SIZE = 10

A_KEY = 'o'
A_GAP = ' '
A_BIG_GAP = '	'
A_BOTTOM_GAP = '_'
A_END = 'n'
A_ROW = 'r'
A_OFFSET_1 = 1
A_OFFSET_2 = 2
A_OFFSET_3 = 3
A_OFFSET_4 = 4
A_OFFSET_5 = 5

OFFSETS = {
    1: -round(ROW_OFFSET * 0.636),
    2: -round(ROW_OFFSET * 0.986),
    3: -round(ROW_OFFSET * 0.636),
    4: -round(ROW_OFFSET * 0.60),
    5: -round(ROW_OFFSET * 0.350)
}

MAX_OFFSET = OFFSETS[max(OFFSETS, key=OFFSETS.get)] * -1
MIN_OFFSET = OFFSETS[min(OFFSETS, key=OFFSETS.get)] * -1

IMAGE_KEY_MAP = {
    'KC_TRNS': {
        'filename': 'transparent.png'
    },
    'KC_NO': {
        'filename': 'noop.png'
    }
}

parser = ArgumentParser()
parser.add_argument("--with-base-layers", help="number of base layers", type=int)
parser.add_argument("--base-layer", help="base layer ID", type=int)

args = parser.parse_args()

if args.with_base_layers and args.base_layer is None:
    print("Base layer ID is required when managing base layers\n")
    parser.print_help()
    exit(1)

keyboard_width = KEY_WIDTH * NUM_COLS + (NUM_COLS - 1) * KEY_GUTTER
keyboard_height = KEY_WIDTH * NUM_ROWS + (NUM_ROWS - 1) * KEY_GUTTER

with open('keymap.json', 'r') as f:
    keyboard = json.loads(f.read())

layers = keyboard['layers']
layer_count = len(layers)
skip_layers = []

if args.with_base_layers:
    layer_count = layer_count - args.with_base_layers + 1

    for layer_idx in range(0, args.with_base_layers):
        if layer_idx != args.base_layer:
            skip_layers.append(layer_idx)

image_width = keyboard_width + IMAGE_PADDING * 2 + GAP
image_height = keyboard_height * layer_count \
    + (layer_count - 1) * KEYBOARD_GUTTER \
    + IMAGE_PADDING * 2 \
    + layer_count * TITLE_GUTTER \
    + MIN_OFFSET - MAX_OFFSET

layout_image = Image.new('RGB', (image_width, image_height), color = 'white')
key_image = Image.open('key.png')

for keycode in IMAGE_KEY_MAP:
    IMAGE_KEY_MAP[keycode]['image'] = Image.open(IMAGE_KEY_MAP[keycode]['filename'])

draw = ImageDraw.Draw(layout_image)
font = ImageFont.truetype(TTF_FONT_PATH, FONT_SIZE)

layout_map = [
    [A_KEY], [A_KEY, A_OFFSET_1], [A_KEY, A_OFFSET_2], [A_KEY, A_OFFSET_3], [A_KEY, A_OFFSET_4], [A_BIG_GAP, A_OFFSET_4], [A_KEY, A_OFFSET_3], [A_KEY, A_OFFSET_2], [A_KEY, A_OFFSET_1], [A_KEY], [A_KEY], [A_END],
    [A_KEY], [A_KEY, A_OFFSET_1], [A_KEY, A_OFFSET_2], [A_KEY, A_OFFSET_3], [A_KEY, A_OFFSET_4], [A_BIG_GAP, A_OFFSET_4], [A_KEY, A_OFFSET_3], [A_KEY, A_OFFSET_2], [A_KEY, A_OFFSET_1], [A_KEY], [A_KEY], [A_END],
    [A_KEY], [A_KEY, A_OFFSET_1], [A_KEY, A_OFFSET_2], [A_KEY, A_OFFSET_3], [A_KEY, A_OFFSET_4], [A_KEY], [A_KEY], [A_GAP], [A_KEY], [A_KEY, A_OFFSET_4], [A_KEY, A_OFFSET_3], [A_KEY, A_OFFSET_2], [A_KEY, A_OFFSET_1], [A_KEY], [A_KEY], [A_END, A_ROW, A_OFFSET_3],
    [A_KEY, A_OFFSET_3], [A_KEY, A_OFFSET_5], [A_KEY], [A_KEY], [A_BOTTOM_GAP], [A_KEY], [A_KEY, A_OFFSET_5], [A_KEY, A_OFFSET_3], [A_KEY, A_OFFSET_3], [A_KEY], [A_KEY]
]

def draw_key(x, y, keycode):
    layout_image.paste(key_image, (x, y))

    try:
        text_width, text_height = IMAGE_KEY_MAP[keycode]['image'].size
        text_x = int(x + KEY_WIDTH / 2 - text_width / 2)
        text_y = int(y + KEY_WIDTH / 2 - text_height / 2)

        layout_image.paste(IMAGE_KEY_MAP[keycode]['image'], (text_x, text_y))
    except KeyError:
        try:
            text = KEYCODES[keycode]
        except KeyError:
            text = keycode

        text_width, text_height = draw.textsize(text)
        text_x = x + KEY_WIDTH / 2 - text_width / 2
        text_y = y + KEY_WIDTH / 2 - text_height / 2

        draw.text((text_x, text_y), text, fill=(0,0,0,128), font=font, align='center')

x = IMAGE_PADDING
y = IMAGE_PADDING + MAX_OFFSET

offset = 0
layer_count = 0

for layer_idx in range(0, len(keyboard['layers'])):
    if layer_idx in skip_layers:
        continue

    text = 'Layer %d' % layer_count
    layer = keyboard['layers'][layer_idx]

    text_width, text_height = draw.textsize(text)
    text_x = image_width / 2 - text_width / 2

    draw.text((text_x, y), text, fill=(0,0,0,128), font=font, align='center')

    y += TITLE_GUTTER
    key_idx = 0

    for text in layer:
        actions = layout_map[key_idx]
        key_idx += 1

        draw_key(x, y + offset, text)

        offset = 0

        for action in actions:
            if action == A_KEY:
                x += KEY_WIDTH + KEY_GUTTER
            elif action == A_GAP:
                x += KEY_WIDTH + GAP
            elif action == A_BIG_GAP:
                x += KEY_WIDTH + BIG_GAP
            elif action == A_BOTTOM_GAP:
                x += BOTTOM_GAP
            elif action == A_END:
                x = IMAGE_PADDING
                y += KEY_WIDTH + KEY_GUTTER
                offset = 0
            elif action == A_ROW:
                x += ROW_INDENT
            elif action in [A_OFFSET_1, A_OFFSET_2, A_OFFSET_3, A_OFFSET_4, A_OFFSET_5]:
                offset = OFFSETS[action]


    x = IMAGE_PADDING
    y += KEYBOARD_GUTTER + KEY_WIDTH + KEY_GUTTER
    layer_count += 1

layout_image.save('layout.png')
