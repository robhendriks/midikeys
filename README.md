# midikeys

Utility that simulates keyboard input based on MIDI messages.

![Screenshot](docs/images/screenshot.jpg)

> ⚠️ This project is work in progress and does not (yet) support dynamic device mappings.

## Platforms

- Windows

## Supported Devices

| Manufacturer | Device | Support |
| --- | --- | --- |
| Novation | Launchpad X | 🟢 Full |

## Usage

**Global Arguments**

| Argument | Alias | Type | Description |
| :------- | :---- | :--: | :---------- |
| `--verbose` | `-v` | boolean | Enable extended logging |

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