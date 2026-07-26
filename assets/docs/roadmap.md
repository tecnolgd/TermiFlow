<!--Roadmap.md-->
## Roadmap & Future Upgrades

- ✓ **Current:** 
  - C++ core with modular architecture    
  - Currently Windows-optimized. Linux/macOS support coming soon.
  - **Makefile** added for modular build and run.
  - Detailed Architecture breakdown and tool info in `assets/docs/architecture.md`
  - **Service-oriented** architecture with proper layer separation
  - **ApplicationService** orchestration pattern
  - **UIService** for centralized presentation logic
  - **ConfigService** for isolated file I/O
  - Feature modules with clear responsibilities
  - RAII for improved exception safety and reduced memory leaks
  - Unit testing suite
  - Consistent error handling across core and feature modules using modern C++ exception handling
  - Config Documentation 
  - Parallel builds in CI for reduced build time

- ◴ **In Progress:** 
  - Implemetation of Arch. diagrams and docs 
  - Logging improvements

- ◌ **Planned:**
  - Cross-platform support (Linux, macOS)
  - Plugin system for third-party modules
  - Enhanced system stats (CPU, network, etc.)
  - Scripting and automation features
  - Additional themes and customization options
  - Benchmarking suite
  - Automated testing and mocking support
  - Performance optimizations
  - cmake for efficient tool build and run

## Suggested Future Improvements(based on ROI)

### **Short Term**
1. Add proper error handling and logging
2. Create abstraction layer for platform-specific code
3. Implement input validation
4. Add unit tests
5. Document file format specifications

### **Medium Term**
1. Refactor to use dependency injection
2. Create plugin/extension architecture
3. Implement async operations
4. Add configuration UI
5. Better error messages and recovery

### **Long Term**
1. Database backend (SQLite) for history/shortcuts
2. Distributed session management
3. REST API for remote access
4. GUI wrapper option
5. Scripting language support