# midikeys

<picture align="right">
  <source media="(prefers-color-scheme: dark)" srcset="./docs/images/logo-dark.svg">
  <img alt="Logo" width="128" height="128" src="./docs/images/logo-light.svg">
</picture>

Command-line utility that dynamically maps MIDI messages to keyboard events.

## Features

- Cross-playform
- Configuration based (YAML) [device profiles](docs/device-profiles.md) & [application mappings](docs/application-mappings.md)

## Operating Systems

- Windows
- macOS

## F.A.Q.

> Which devices are supported?

Any MIDI-capable device is supported, just select (or create) a profile that fits your needs.

Click [here](docs/supported-devices.md) for a full list of built-in [device profiles](docs/device-profiles.md).

> Which applications are supported?

Any application that accepts keyboard shortcuts will work with midikeys, as long as the window is active.

Click [here](docs/supported-applications.md) for a full list of built-in [application mappings](docs/application-mappings.md).

## Usage

### CLI

**Global Arguments**

| Argument    | Alias | Type    | Description             |
| ----------- | ----- | ------- | ----------------------- |
| `--verbose` | `-v`  | boolean | Enable extended logging |

#### List MIDI Ports

```shell
midikeys --list
```

#### Verify Configuration

```shell
midikeys --verify <mapping> <device_profile>
```

##### Example

```shell
midikeys --verify rekordbox novation-launchpad-x
```

#### Run

```shell
midikeys --input=<port> --output=<port> <mapping> <device_profile>
```

##### Example

```shell
midikeys --input=0 --output=0 rekordbox novation-launchpad-x
```
