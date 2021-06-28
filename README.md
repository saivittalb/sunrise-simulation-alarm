# Sunrise Simulation Alarm

[![License](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![PR's Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat)](http://makeapullrequest.com)
[![GitHub followers](https://img.shields.io/github/followers/saivittalb.svg?style=social&label=Follow)](https://github.com/saivittalb?tab=followers)
[![Twitter Follow](https://img.shields.io/twitter/follow/saivittalb.svg?style=social)](https://twitter.com/saivittalb)

An Arduino Nano based sunrise simulating alarm clock. All interfacing is done through I2C protocol and the design works efficiently.

The working prototype can be briefly viewed [here](https://user-images.githubusercontent.com/36305142/123651983-888baf00-d849-11eb-85a4-524fbc1135b1.jpeg).

Working code for the project can be viewed in ```Sunrise_Simulation``` directory and can be simulated by downloading the code and the provided ```libraries``` directory. Only one LED is used for demo purpose. Multiple WS2812B LEDs can be soldered together and can be used. The current LED is set to simulate when the current hour and the alarm hour is matching. This code algorithm is invain in real-world scenario and will be updated in the future.

It is to be noted that the actual boost converter used in the prototype is XL6009 and is different from the component showed in the Fritzing schematic. Also, the LiPo battery capacity of 2500 mAh is used for the prototype while the schamtic shows LiPo capacity of 2000 mAh. These two components were slightly deffered since Fritzing doesn't have these components with exact specifications.

Developed as a part of PR 301 - Embedded Hardware Project under the supervision of Dr. KR Sarma and Dr. Bharghava Rajaram. Design specifications can be viewed in a report submitted before the development of the hardware prototype in ```Final-Report.docx```. The report remains slightly obsolete after the hardware implementation.

## Table of contents

* [License](#license)
* [Requirements](#requirements)
* [Schematic](#schematic)
* [Contributing](#contributing)

## License

This project is licensed under the MIT License, a short and simple permissive license with conditions only requiring preservation of copyright and license notices. Licensed works, modifications and larger works may be distributed under different terms and without source code.

<p align="center"> Copyright (c) 2021 Sai Vittal B. All rights reserved.</p>

## Requirements

* 1 x Arduino Nano
* Arduino IDE
* 1 x DS1307 RTC Module
* 1 x 20x4 LCD Display
* WS2812B RGB LEDs
* 1 x LiPo 3.7V 2500 mAh Battery
* 1 x XL6009 Boost Converter Module
* 1 x TP4056 Battery Charging Module
* 1 x I2C adapter
* 4 x Push Buttons
* 1 x 330 Ω Resistor
* Jumper Wires (Male-Male, Male-Female, Female-Female)
* Fritzing

## Schematic

Schematic, PCB and Breadboard connections can be view in the ```Sunrise-Simulation-Alarm.fzz``` in ```Fritzing``` directory.

The following is a screenshot of the final breadboard schematic captured on Fritzing.

![Breadboard Schematic](https://user-images.githubusercontent.com/36305142/123655361-870fb600-d84c-11eb-8ad1-d0e82ec60964.png)

## Contributing

* Fork this project by clicking the ```Fork``` button on top right corner of this page.
* Open terminal/console window.
* Clone the repository by running following command in git:

```bash
$ git clone https://github.com/[YOUR-USERNAME]/sunrise-simulation-alarm.git
```

* Add all changes by running this command.

```bash
$ git add .
```

* Or to add specific files only, run this command.

```bash
$ git add path/to/your/file
```

* Commit changes by running these commands.

```bash
$ git commit -m "DESCRIBE YOUR CHANGES HERE"

$ git push origin
```

* Create a Pull Request by clicking the ```New pull request``` button on your repository page.

[![ForTheBadge built-with-love](http://ForTheBadge.com/images/badges/built-with-love.svg)](https://GitHub.com/saivittalb/)
[![ForTheBadge powered-by-electricity](http://ForTheBadge.com/images/badges/powered-by-electricity.svg)](http://ForTheBadge.com)

<p align="center"> Copyright (c) 2021 Sai Vittal B. All rights reserved.</p>
<p align="center"> Made with ❤ by <a href="https://github.com/saivittalb">Sai Vittal B</a></p>
