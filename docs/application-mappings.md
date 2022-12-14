# Application Mappings

Mappings are defined in `yaml` and allow you to dynamically bind MIDI events to key strokes.

```yaml
# Rekorbox
mapping:
  # CC Channel 1, Control 21-28
  - range:
      type: button
      midi:
        channel: 1
        control: [21, 28] # Create 8 buttons (21...28)
      keyboard: [q, w, e, r, t, y, u, i]
      color: green

  # CC Channel 1, Control 13
  - button:
      midi: [1, 13]
      keyboard: [arrow_left]
      color: orange

  # CC Channel 1, Control 14
  - button:
      midi: [1, 14]
      keyboard: [arrow_left]
      color: red
```
