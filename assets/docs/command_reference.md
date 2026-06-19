<!--command_reference.md-->

### Starting TermiFlow
Once launched, TermiFlow operates in a command-driven terminal mode where you can:

### Available Commands (for command - handler mode)

#### Application Launcher
Launch system applications directly from the terminal:
```bash
launch chrome          # Opens Chrome browser
launch code            # Opens VS Code editor
launch [application]   # Launch any registered application
```

#### Custom Shortcuts
Define and use custom shortcuts for frequently used commands:
```bash
shortcut add chrome c          # Add shortcut 'c' for chrome
shortcut list                  # View all shortcuts
shortcut remove c                            # Remove the shortcut 'c' for chrome.
```

#### Command History
View previously executed commands:
```bash
history list                        # Display command history
history clear                       # Clear command history
history goto [index]                # Display the command at the given history index.
```

#### Theme Management
Switch between light and dark themes:
```bash
theme dark                     # Switch to dark theme
theme light                    # Switch to light theme
```

#### System Stats
View system information:
```bash
stats                          # Display CPU (N/A), Memory, Uptime (Windows-focused)
``` 