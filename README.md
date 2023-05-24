# QHTMLPen

QHTMLPen is a text editor based on Qt that allows you to edit and display HTML code. It supports Windows and Ubuntu platforms.

## Description

We built this project as a way to practice our skills in Qt. We wanted to create a simple but powerful editor that can help write and preview HTML code easily. This project solves the problem of having to switch between different applications or tabs to see the output of HTML code. We use Qt widgets, signals and slots, and QWebEngineView to create a user interface and render HTML code. This project stands out because it is cross-platform, lightweight, and fast.

## Table of Contents
- [Installation](#installation)
- [Usage](#usage)
- [Contribution](#contribution)
- [License](#license)

## Installation

To build this project, you will need Qt 6.2 or higher and a C++17 compiler. You need to use qmake to generate a Makefile or a project for your IDE. For example:

```bash
# qmake
qmake QHTMLPen.pro make

# Run the executable
./QHTMLPen
```

## Usage

To use this project, you can open an existing HTML file or create a new one. You can edit the HTML code and see the output by clicking "Ctrl+R". You can also save your changes.

## Contribution

To contribute to this project, you can follow these steps:

- Fork this repository and clone it to your local machine.
- Create a new branch from master with the name developer-name.
- Develop your code in this branch and make commits with meaningful messages that describe what you did or changed.
- When your code is ready for review, create a pull request from your branch to master and add other developers as reviewers.
- After getting approval from reviewers and passing all checks, you can merge your pull request to master.
- After all tasks or features for a new version of the program are merged to master, you can create a pull request from master to release and add the maintainer of the project as a reviewer.
- After getting approval from the maintainer and passing all checks, you can merge your pull request to release and create a new tag with the version number.

## License

QHTMLPen is an open source project that is distributed under the GNU General Public License v3.0 (GPLv3). This means that you can freely use, copy, modify and distribute this project, provided that you keep this license and acknowledge the original authorship of this project. You also have to make available the source code of any modifications or derivative works that you create based on this project.
