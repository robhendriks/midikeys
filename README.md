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

### List MIDI ports

```shell
midikeys --list
```

### Run

```shell
midikeys --input=<port> --output=<port> <mapping_file>
```

**Example**

```shell
midikeys --input=0 --output=0 "mappings/rekordbox.toml"
```

## Mappings

Mapping can be defined in `toml`. The root of a mapping file always contains an array of tables `[[inputs]]`, you can
use the array entries to specify mapping from a specific MIDI CC message to a key press.

```toml
# Map MIDI CC11 to arrow_left
[[inputs]]
channel = 1 # MIDI CC Channel
control = 11 # MIDI CC Control
key = "arrow_left"
feedback = { off = "dark_red", on = "light_red" } # Specify on and off colour

# ... <inputs>
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

Device profiles can be defined in `toml`. The following snippet is a short example device profile for the Novation
Launchpad X.

```toml
[messages]
# MIDI message(s) sent when the connection is open
open = [[240, 0, 32, 41, 2, 12, 14, 1, 247]] # Switch programmer layout
# MIDI message(s) sent when the connection will be closed
close = [[240, 0, 32, 41, 2, 12, 14, 0, 247]] # Switch back to live layout

[colours]
dark_red = 7 # Map to MIDI CC value
light_red = 5 # Map to MIDI CC value
```
