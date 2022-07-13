# Feuerwehr Spritzenhäuschen (mit Mikrocontroller)

> This reposity is an archive of a very old project. Feel free to contribute to make this usable and understandable to more people!
> I will add more explaining pictures and a circuit schematic as soon as possible.

## Introduction

This repository contains very simple source code that might be used with a wooden house as depicted here:
![Wooden house with flames that can fall over.](https://raw.githubusercontent.com/neumicha/fw-spritzenhaus/main/media/img_house.jpg)
When all the flames are fallen over, some actions are triggered.
We use this in the local youth fire brigade for interested kids. They can "extinguish the fire" with a small water hose. After all eight flames are fallen, we trigger a flashing blue light, a horn/siren and play some music.

> !!!Attention!!!
> This code is really old and unfortunatelly contains only german comments. Sorry for this. Furthermore it is kept really simple to allow people that are new to microcontrollers to understand it and adapt it to their use case.

## Why using a microcontroller

Using a microcontroller for this seems a bit overkill.
We reviewed some other builds from other fire brigades beforehand. We found out that very simple builds suffer from rusting after using them a few times. Furthermore using just some copper contacts to close the circuit means major limitations as trigger actions.

So we decided to build a luxury version with:

* 12V power supply for a car battery (allows to connect many common fire brigade "gadgets" like a siren/blue light)
* Microcontroller to trigger multiple actions in the defined order
* Reed contacts with a magnet on each flame instead of copper contacts (no rusting)

![Circuit board.](https://raw.githubusercontent.com/neumicha/fw-spritzenhaus/main/media/img_board-top.jpg)

## Usage

Unfortunatelly, I can not provide a circuit schematic yet. I'll add a scan of the manually written diagram asap.

The circuit is ment to be used with some "user interface":

* 8 LEDs displaying the status of each flame
* 1 LED showing the status ("armed"/"unarmed/already triggered")
* 1 Pushbutton to "arm" the circuit

## Contributing

I am glad about any support. Feel free to create a merge request if you add new features, improve the existing code, ...
Current ToDos:

* Translate german code comments to english language
* Create digital circuit schematic