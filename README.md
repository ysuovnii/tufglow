# TUFGlow

A lightweight command-line RGB controller for ASUS TUF laptop keyboards on Linux.

TUFGlow uses the Linux sysfs interface exposed by the ASUS kernel driver to control keyboard brightness and RGB colors.

## Features

* Set keyboard brightness
* Turn keyboard lighting off
* Set predefined colors
  * Red
  * Green
  * Blue
  * White
* Set custom RGB colors
* Simple interactive terminal interface
* No external libraries required

## Requirements

* Linux
* ASUS TUF laptop with supported RGB keyboard
* C++17 compiler
* `g++`
* `git`
* Root privileges when running TUFGlow

TUFGlow currently uses:

```text
/sys/class/leds/asus::kbd_backlight/
```

Your system should have:

```text
kbd_rgb_mode
kbd_rgb_mode_index
brightness
```

You can check with:

```bash
ls /sys/class/leds/asus::kbd_backlight/
```

## Installation

Clone the repository:

```bash
git clone https://github.com/ysuovnii/tufglow.git
```

Enter the project directory:

```bash
cd tufglow
```

Run the installer:

```bash
./install.sh
```

The installer will:

1. Compile TUFGlow using `g++`
2. Create the `build` directory
3. Install the executable to:

```text
~/.local/bin/tufglow
```

4. Make the executable runnable

### If `./install.sh` is not executable

Run:

```bash
chmod +x install.sh
```

Then:

```bash
./install.sh
```

## Running TUFGlow

TUFGlow requires root privileges to access the ASUS keyboard sysfs interface.

Run:

```bash
sudo tufglow
```

You should see:

```text
tufglow - ASUS TUF RGB controller
Type 'help' for commands.

tufglow ❯
```

## Commands

### Red

```text
red
```

Sets the keyboard to red.

### Green

```text
green
```

Sets the keyboard to green.

### Blue

```text
blue
```

Sets the keyboard to blue.

### White

```text
white
```

Sets the keyboard to white.

### Custom RGB

```text
rgb <r> <g> <b>
```

RGB values range from `0` to `255`.

Example:

```text
rgb 255 100 20
```

This produces an orange-like color.

Another example:

```text
rgb 128 0 255
```

This produces a purple-like color.

### Brightness

```text
brightness <0-3>
```

Example:

```text
brightness 3
```

Brightness levels:

```text
0 = Off
1 = Low
2 = Medium
3 = High
```

### Turn off

```text
off
```

Turns the keyboard lighting off.

### Help

```text
help
```

Displays the available commands.

### Exit

```text
quit
```

or:

```text
exit
```

## Example Session

```text
$ sudo tufglow

tufglow - ASUS TUF RGB controller
Type 'help' for commands.

tufglow ❯ red
tufglow ❯ brightness 3
tufglow ❯ rgb 255 50 100
tufglow ❯ blue
tufglow ❯ off
tufglow ❯ quit
```

## How It Works

TUFGlow communicates directly with the Linux ASUS keyboard LED interface.

The RGB interface is:

```text
/sys/class/leds/asus::kbd_backlight/kbd_rgb_mode
```

The system exposes the following fields:

```text
cmd mode red green blue speed
```

For static RGB colors, TUFGlow writes values in the following format:

```text
1 0 R G B 0
```

For example, red is:

```text
1 0 255 0 0 0
```

Green:

```text
1 0 0 255 0 0
```

Blue:

```text
1 0 0 0 255 0
```

Keyboard brightness is controlled through:

```text
/sys/class/leds/asus::kbd_backlight/brightness
```

## Building Manually

You can also compile TUFGlow without the installer:

```bash
mkdir -p build

g++ -std=c++17 src/main.cpp -o build/tufglow
```

Run it with:

```bash
sudo ./build/tufglow
```

## Project Structure

```text
tufglow/
├── src/
│   └── main.cpp
├── build/
├── Makefile
├── install.sh
└── README.md
```

## Uninstall

Remove the installed executable:

```bash
rm ~/.local/bin/tufglow
```

The source code can then be removed normally:

```bash
rm -rf tufglow
```

## Troubleshooting

### `tufglow: command not found`

Make sure `~/.local/bin` is in your `PATH`:

```bash
echo $PATH
```

If it is missing, add:

```bash
export PATH="$HOME/.local/bin:$PATH"
```

For a permanent change, add that line to your shell configuration file.

### Permission denied

Run TUFGlow with root privileges:

```bash
sudo tufglow
```

### RGB does not work

Check whether your system exposes the ASUS RGB interface:

```bash
ls /sys/class/leds/asus::kbd_backlight/
```

Then check:

```bash
cat /sys/class/leds/asus::kbd_backlight/kbd_rgb_mode_index
```

A supported system should expose something similar to:

```text
cmd mode red green blue speed
```

## Contributing

Contributions, bug reports, and improvements are welcome.

If you find a problem with TUFGlow on another ASUS TUF model, please open an issue with:

* Laptop model
* Linux distribution
* Kernel version
* Output of:

```bash
cat /sys/class/leds/asus::kbd_backlight/kbd_rgb_mode_index
```

## License

This project is open source. See the repository for license information.

