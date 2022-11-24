# Device Profiles

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
