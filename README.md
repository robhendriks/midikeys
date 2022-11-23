# midikeys

Utility that simulates keyboard input based on MIDI messages.

![Screenshot](docs/images/screenshot.jpg)

> ⚠ Currently only supports keyboard with a European QWERTY layout.

## Platforms

- Windows
- macOS (t.b.d)

## Supported Devices

| Manufacturer | Device      | Support |
|--------------|-------------|---------|
| Novation     | Launchpad X | 🟢 Full |

> ℹ You can add support for any device using [device profiles](#device-profiles).

## Supported Applications

| Developer | Application | Support |
| --------- | ----------- | ------- |
| Pioneer   | rekordbox   | 🟢 Full |

> ℹ You can add support for any application using [mappings](#mappings).

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
# Rekorbox
mapping:
  # Map MIDI CC 13 to left arrow
  - control_change:
      channel: 1
      control: 13
      keys:
        # Single keystroke
        - arrow_left
      # Maps to color 'red' defined in the device profile
      color: red

  # Map MIDI CC 14 to right arrow
  - control_change:
      channel: 1
      control: 14
      keys:
        # Multiple keystrokes
        - shift_left
        - arrow_right
      # Maps to color 'green' defined in the device profile
      color: green
```

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
# Novation Launchpad X
profile:
  messages:
    # MIDI messages to send when connected
    open:
      - sysex: [240, 0, 32, 41, 2, 12, 14, 1, 247] # Select progammer layout
      - sysex: [240, 0, 32, 41, 2, 12, 8, 127, 247] # Max brightness
      - sysex: [240, 0, 32, 41, 2, 12, 4, 3, 127, 247] # Fixed velocity curve
    # MIDI messages to send before connection closes
    close:
      - sysex: [240, 0, 32, 41, 2, 12, 14, 0, 247] # Select live layout

  # Color to MIDI mapping
  # color_name: [on CC value, off CC value]
  colors:
    red: [7, 5]
    green: [23, 21]
    blue: [47, 45]
    cyan: [39, 37]
    magenta: [55, 53]
    yellow: [15, 13]
    orange: [10, 9]
    pink: [56, 57]
```
