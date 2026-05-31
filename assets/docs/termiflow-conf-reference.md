# termiflow.conf Configuration Reference

## Overview
The `termiflow.conf` file is the main configuration file for TermiFlow.
It controls the behavior of the terminal productivity tool.

## File Location
Place the configuration file in the root directory of your project:
## Structure

```ini
[general]
version = 1.0
debug = false

[display]
theme = dark
font_size = 14
show_line_numbers = true

[performance]
cache_enabled = true
max_threads = 4
```

## Configuration Options

### [general]
| Key | Type | Default | Description |
|-----|------|---------|-------------|
| version | string | 1.0 | Config file version |
| debug | boolean | false | Enable debug mode |

### [display]
| Key | Type | Default | Description |
|-----|------|---------|-------------|
| theme | string | dark | UI theme (dark/light) |
| font_size | integer | 14 | Terminal font size |
| show_line_numbers | boolean | true | Show line numbers |

### [performance]
| Key | Type | Default | Description |
|-----|------|---------|-------------|
| cache_enabled | boolean | true | Enable caching |
| max_threads | integer | 4 | Maximum thread count |
