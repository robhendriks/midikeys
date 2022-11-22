# midikeys

Utility that simulates keyboard input based on MIDI messages.

![Screenshot](docs/images/screenshot.jpg)

> ⚠️ This project is work in progress and does not (yet) support dynamic device mappings.

## Platforms

- Windows

## Supported Devices

| Manufacturer | Device      | Support |
|--------------|-------------|---------|
| Novation     | Launchpad X | 🟢 Full |

## Usage

**Global Arguments**

| Argument    | Alias | Type    | Description             |
|-------------|-------|---------|-------------------------|
| `--verbose` | `-v`  | boolean | Enable extended logging |

### List MIDI Ports

```shell
midikeys --list
```

### Verify Configuration

```shell
midikeys --verify <mapping> <device_profile>
```

**Example**
```shell
midikeys --verify rekordbox novation-launchpad-x
```

### Run

```shell
midikeys --input=<port> --output=<port> <mapping> <device_profile>
```

**Example**

```shell
midikeys --input=0 --output=0 rekordbox novation-launchpad-x
```

## Mappings

Mappings are defined in `yaml` and allow you to dynamically bind MIDI events to key strokes.

```yaml
mappings:
  # MIDI CC 11 to left arrow
  - channel: 1
    control: 11
    key: arrow_left
    feedback:
      off: dark_red
      on: light_red

  # MIDI CC 12 to right arrow
  - channel: 1
    control: 12
    key: arrow_right
    feedback:
      off: dark_red
      on: light_red
```

### Color Table

| Colour      |
|-------------|
| `light_red` |
| `dark_red`  |

### Key Table

| ID            | Key         |
|---------------|-------------|
| `arrow_left`  | Arrow Left  |
| `arrow_right` | Arrow Right |
| `arrow_up`    | Arrow Up    |
| `arrow_down`  | Arrow Down  |

## Device Profiles

Devices profiles allow users to add support for a specific MIDI device.

```yaml
# Messages sent upon opening or closing the MIDI connection
messages:
  open:
    - [240, 0, 32, 41, 2, 12, 14, 1, 247] # Select programmer layout
  close:
    - [240, 0, 32, 41, 2, 12, 14, 0, 247] # Select live layout

# Color -> MIDI CC value mapping
colors:
  dark_red: 7
  light_red: 5
```
