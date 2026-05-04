# TermiFlow Architecture Documentation

## Project Overview

>- TermiFlow is a **command-driven terminal application** written in C++ that provides a centralized hub for launching applications, managing shortcuts, tracking command history, and viewing system information.      
>-  It operates as a menu-driven CLI tool with modular component architecture.

**Technology Stack:**

- **Language:** C++ (C++11 and later)
- **Compiler:** g++ or MinGW (for Windows)
- **Platform:** Linux/Windows (cross-platform via conditional compilation)
- **Configuration:** Plain text config file (INI-like format)
- **Data Storage:** File-based (shortcuts, history, config)


## Core Design Philosophy

- **Service-oriented architecture** – clean separation of concerns between business logic, UI, and data layers
- **Dependency injection** – services are initialized and injected into the application layer
- **C++ first** – performance, control, and systems-level understanding  
- **Extensible by design** – new commands can be added without rewriting core logic  
- **Terminal-native** – works where developers already live
- **Testability** – business logic decoupled from UI and I/O operations


## Component Architecture

### Architecture Layers

TermiFlow follows a **three-layer service-oriented architecture**:

### 1. Entry Point: main.cpp

**Responsibility:** Application bootstrap and error handling

**Key Structure:**
- Creates `ApplicationService` instance (dependency container)
- Calls `app.initialize()` to set up configuration and theme
- Calls `app.run()` to start the main application loop
- Minimal code, delegates all logic to ApplicationService

**Current Flow:**
```txt
Application Start
    ↓
Create ApplicationService
    ↓
Initialize (load config, apply theme)
    ↓
Run main loop (orchestrated by ApplicationService)
    ↓
Exception handling and cleanup
```

### 2. Core Services (Service Layer)

#### A. ApplicationService (application_service.hpp/cpp)

**Purpose:** Core business logic orchestration and application control flow

**Responsibilities:**
- Initialize application (load configuration, apply theme)
- Orchestrate main event loop
- Delegate feature requests to appropriate modules
- Handle theme changes and configuration updates
- Manage application state

**Key Methods:**
- `initialize()` - Load config and apply auto-theme if enabled
- `run()` - Main application loop with menu dispatch via switch statement
- `shouldApplyAutoTheme()` - Check auto-theme setting
- `getCurrentTheme()` - Get current theme preference
- `handleThemeChange()` - Coordinate theme change between services

**Dependencies:**
- `ConfigService` - For configuration management
- `UIService` - For user interaction
- Feature modules (Launch, Shortcuts, History, etc.)

**Architecture Pattern:** Dependency injection and facade pattern

#### B. UIService (ui_service.hpp/cpp)

**Purpose:** Centralize all user interface and presentation logic

**Responsibilities:**
- Display menus and prompts to user
- Collect and validate user input
- Format and display messages, errors, and success notifications
- Isolate all I/O operations from business logic

**Key Methods:**
- `displayMainMenu()` - Show main menu
- `getMenuChoice()` - Get and validate menu selection (0-9)
- `getThemeInput()` - Prompt for theme selection
- `displayMessage(message)` - Display generic message
- `displayError(error)` - Display error message
- `displaySuccess(message)` - Display success message
- `getUserInput(prompt)` - Get generic user input

**Key Features:**
- Input validation (ensures numeric choices are digits 0-9)
- Consistent message formatting
- Centralized output - all presentation goes through this service
- Enables easy testing (can be mocked or replaced)

#### C. ConfigService (config_service.hpp/cpp)

**Purpose:** Manage all configuration file I/O and data access

**Responsibilities:**
- Load configuration from `config/termiflow.conf`
- Parse INI-like config file format
- Store configuration in memory (unordered_map)
- Save configuration changes to file
- Provide get/set interface for config values

**Key Methods:**
- `loadConfig()` - Read and parse config file
- `saveConfig()` - Write configuration back to file
- `getValue(key, defaultValue)` - Retrieve config value
- `setValue(key, value)` - Update config value
- `getConfig()` - Get entire configuration object

**Data Structure:**
```cpp
struct Config {
    std::unordered_map<std::string, std::string> values;
};
```

**Config Keys:**
- `user_interface.theme` - Current theme (light/dark)
- `user_interface.show_banner` - Show banner on startup
- `behavior.auto_apply_theme` - Auto-apply theme on startup

**File Format:**
```ini
[user_interface]
theme=dark
show_banner=true

[behavior]
auto_apply_theme=true
```

### 3. Feature Modules

#### A. Theme Manager (theme_manager.hpp/cpp)

**Purpose:** Apply and manage terminal color themes

**Key Functions:**
- `changeTheme(std::string theme)` - Apply named theme to terminal
- `changeTheme()` - Interactive theme selection (deprecated, use UIService)

**Supported Themes:** Light, Dark (platform-dependent ANSI codes)

**Implementation:** Uses ANSI escape sequences for terminal color control

> **Note:** In the new SOC architecture:     
> - Theme application logic is isolated in this module
> - Theme persistence is handled by `ConfigService`
> - Theme UI interaction is delegated to `UIService`
> - ApplicationService coordinates between these services

#### B. Launcher (launch.hpp/cpp)

**Purpose:** Execute/launch system applications

**Key Functions:**
- `launchApp()` - Interactive app selection and launching
- `launchApp(std::string appName)` - Direct app launch by name

**Functionality:**
- Presents list of available applications to user
- User selects application to launch
- Executes application via system/platform-specific calls

**Platform Support:**
- Linux: Uses `execvp()` or similar system call
- Windows: Uses `CreateProcess()` or `system()` call

**Integration:** Called by `ApplicationService` on menu option '1'

#### C. Shortcuts (shortcuts.hpp/cpp)

**Purpose:** Define and manage custom command shortcuts

**Architecture:** Class-based with in-memory state management

```cpp
class shortcuts {
    // Storage
    std::unordered_map<std::string, std::string> shortMap;
    std::string filepath;
    
    // Methods
    void add(const std::string& key, const std::string& value);
    void remove(const std::string& key);
    void save();
    void list();
    void load();
    bool exists(const std::string& value);
    std::string getValue(const std::string& key);
};
```

**Key Features:**
- In-memory HashMap for O(1) lookup
- File persistence (unknown format)
- Add/remove/list/search operations
- Interactive mode (`shortcutInteractive()`)

**Integration:** Called by `ApplicationService` on menu option '2'

#### D. History (history.hpp/cpp)

**Purpose:** Track and display command history

**Architecture:** Class-based with vector storage

```cpp
class history {
    std::string filePath;
    std::vector<std::string> cmdEntries;
    
    void load();
    void save();
    void add(const std::string& cmd);
    void list();
    std::string get(int index);
    void historyClear();
};
```

**Key Features:**
- In-memory vector storage (ordered)
- File persistence
- Add/list/clear/index operations
- Interactive mode (`historyInteractive()`)

**Integration:** Called by `ApplicationService` on menu option '6'

#### E. Session Manager (session_manager.hpp/cpp)

**Purpose:** Manage sessions and running tasks

**Status:** Planned for future implementation

**Integration:** Called by `ApplicationService` on menu option '3'

#### F. System Stats (system_stats.hpp/cpp)

**Purpose:** Display system information and statistics

**Status:** Partially implemented

**Key Functions:**
- `statsInteractive()` - Display system statistics

**Integration:** Called by `ApplicationService` on menu option '7'

#### G. Command Handler (command_handler.hpp/cpp)


## Data Flow Diagrams

### Application Initialization Flow

```txt
main() starts
    ↓
Create ApplicationService instance
    ├─ Initializes ConfigService (loads config/termiflow.conf)
    ├─ Initializes UIService
    └─ Initializes ThemeManager
    ↓
app.initialize()
    ├─ Load config via ConfigService
    ├─ Check auto_apply_theme setting
    └─ Apply theme if enabled
    ↓
app.run() - Enter main loop
```

### Main Event Loop Flow
```txt
UIService.displayMainMenu()  [UI Layer]
    ↓
UIService.getMenuChoice()  [UI Layer]
    ↓
ApplicationService.run()  [Business Logic Layer]
    ├─ Validate choice (0-9)
    └─ Dispatch via switch statement
    ↓
Feature module (Launch, Shortcuts, History, etc.)
    ├─ Perform business logic
    ├─ Use ConfigService for data access [Data Layer]
    └─ Use UIService for user interaction [UI Layer]
    ↓
Return to menu loop
```

### Theme Change Flow

```txt
User selects "4. Change theme"
    ↓
ApplicationService.handleThemeChange()  [Business Logic]
    ├─ UIService.getThemeInput()  [UI Layer]
    │   └─ Display theme options and collect input
    ├─ ThemeManager.changeTheme(theme)  [Feature Layer]
    │   └─ Apply ANSI codes to terminal
    ├─ ConfigService.setValue("user_interface.theme", theme)  [Data Layer]
    ├─ ConfigService.saveConfig()  [Data Layer]
    │   └─ Write to config/termiflow.conf
    └─ UIService.displaySuccess()  [UI Layer]
    ↓
Return to main menu
```

### Feature Feature Module Execution Pattern

```txt
ApplicationService.run()
    ↓
User selects menu option
    ↓
ApplicationService delegates to feature module
    ├─ Feature performs its business logic
    ├─ Feature may call ConfigService for persistence
    ├─ Feature may call UIService for user interaction
    └─ Feature returns to ApplicationService
    ↓
ApplicationService returns to main loop
```

### Shortcuts Management Flow

```txt
User selects "2. Manage shortcuts"
    ↓
ApplicationService.shortcutInteractive()  [Business Logic]
    ├─ Load shortcuts from file
    ├─ Display options via UIService  [UI Layer]
    ├─ Get user choice via UIService  [UI Layer]
    ├─ If add/remove:
    │   ├─ Update in-memory map
    │   ├─ Save to file via persistence
    │   └─ Display success via UIService  [UI Layer]
    └─ If list:
        └─ Display all shortcuts via UIService  [UI Layer]
    ↓
Return to main menu
```

### Command Handler Flow (Alternative Interface)

```txt
User selects "9. Command Handler" (or accessed directly)
    ↓
cmdHandler() main loop starts
    ↓
Display ">>>" prompt
    ↓
Read user input (e.g., "launch chrome")
    ↓
Tokenize input via std::stringstream
    ↓
Extract command (e.g., "launch")
    ↓
Match command and validate arguments
    ↓
Branch to feature handler:
    ├─ "launch": Call launchApp(tokens[1])
    ├─ "theme": Call changeTheme(tokens[1])
    ├─ "shortcut": Call shortcuts.add/remove/list()
    ├─ "history": Call history.add/list/clear/goto()
    ├─ "stats": Call statsInteractive()
    └─ Unknown: Display error and usage info
    ↓
Add command to history
    ↓
Return to command prompt (loop continues)
```

## Known Issues & Improvements

For a comprehensive list of known limitations, ongoing issues, and opportunities to contribute, please refer to the [GitHub Issues](https://github.com/tecnolgd/TermiFlow/issues) tab.    
Each issue is categorized and tracked for priority and difficulty level.

## Conclusion

TermiFlow has evolved into a **clean, service-oriented architecture** that follows separation of concerns principles:

**Key Architectural Improvements:**
- **Clean layers** - UI, business logic, and data access are strictly separated
- **Single responsibility** - Each service has one reason to change
- **Testability** - Services can be tested independently, business logic decoupled from I/O
- **Maintainability** - Feature additions don't require modifications to core services
- **Extensibility** - New features can be added without affecting existing code

The project benefits significantly from this architectural refactoring, making it accessible for contributors and maintainable as new features are added. The codebase is positioned for future enhancements like plugin systems, REST APIs, or database backends without requiring major architectural changes.