# Blood Bank System

A comprehensive C++ application for managing blood bank operations including donor management, blood inventory tracking, and blood request fulfillment.

## Project Overview

This system provides a complete solution for blood banks to:
- Register and manage blood donors
- Track blood units in inventory with expiration dates
- Process blood requests from hospitals and medical facilities
- Generate reports on stock levels and donor eligibility
- Validate blood type compatibility

## Features

### Donor Management
- Register new blood donors with personal information
- Track donor eligibility based on donation history
- Search and view donor details
- List eligible donors for specific blood types
- Remove donor records

### Blood Inventory
- Add new blood units with type, quantity, and collection date
- Track blood units by type (A, B, AB, O and Rh factor)
- Monitor expiration dates and automatically remove expired units
- View stock summary and quantity by blood type
- Remove specific blood units

### Blood Requests
- Create blood requests with urgency levels (Normal, High, Critical)
- Check available inventory for request fulfillment
- Track request status (Pending, Fulfilled, Cancelled)
- Fulfill requests from available stock
- Cancel pending requests

### Reports
- View current stock summary
- List all donors with eligibility status
- Display pending blood requests
- Check blood unit details and availability

## Project Structure

```
BloodBankSystem/
├── main.cpp                 # Entry point of the application
├── CMakeLists.txt          # Build configuration
├── data/                   # Data storage files
│   ├── donors.txt         # Donor records
│   ├── inventory.txt      # Blood unit records
│   └── requests.txt       # Blood request records
├── managers/              # Business logic
│   ├── DonorManager.*     # Donor operations
│   ├── BloodInventory.*   # Inventory operations
│   └── RequestManager.*   # Request operations
├── models/                # Data models
│   ├── Donor.*
│   ├── BloodUnit.*
│   └── Request.*
├── ui/                    # User interface
│   └── Menu.*             # Menu system
└── utils/                 # Utility functions
    ├── FileHandler.*      # File I/O operations
    ├── DateUtils.*        # Date handling
    └── Validator.*        # Input validation
```

## Requirements

- C++17 or higher
- CMake 3.10 or higher
- Visual Studio or compatible C++ compiler

## Building the Project

### Using CMake

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

The executable will be generated in the build directory as `BloodBankSystem.exe`.

## Running the Application

Navigate to the build directory and run:

```bash
./BloodBankSystem.exe
```

Or from the build directory:

```bash
BloodBankSystem.exe
```

## Usage

Upon running the application, you will see a main menu with the following options:

1. **Donor Management** - Add, search, or list donors
2. **Blood Inventory** - Manage blood units
3. **Blood Requests** - Create and fulfill requests
4. **Reports** - View system summaries and reports
5. **Exit** - Close the application

### Main Menu Navigation

The application uses a menu-driven interface. Follow the on-screen prompts to:
- Enter donor information (name, blood type, contact details)
- Specify blood units (type, quantity in ml, collection date)
- Submit blood requests with urgency levels
- View current system status and reports

## Data Files

The application stores data in the `data/` directory:

- **donors.txt** - Contains registered donor information
- **inventory.txt** - Contains all blood units currently in stock
- **requests.txt** - Contains blood request history and status

These files are automatically created and updated by the application.

## Blood Type System

Supported blood types:
- A+ / A-
- B+ / B-
- AB+ / AB-
- O+ / O-

## Key Classes

- **DonorManager** - Handles donor registration, search, and eligibility
- **BloodInventory** - Manages blood units, stock levels, and expiration
- **RequestManager** - Processes blood requests and fulfillment
- **Menu** - Provides the command-line user interface
- **FileHandler** - Manages persistent data storage
- **Validator** - Validates user input and blood type compatibility
- **DateUtils** - Handles date operations and expiration checks

## System Components

### Input Validation
The system validates all user inputs including:
- Blood type compatibility
- Quantity ranges
- Date formats
- Contact information

### Data Persistence
All data is automatically saved to files and restored when the application restarts.

### Expiration Management
The system tracks blood unit expiration dates and can automatically remove expired units.

## Notes

- Blood donation eligibility is tracked to prevent invalid donations
- Request urgency levels affect priority in fulfillment
- Expired blood units are automatically identified but must be manually removed
- All dates are handled in a standard format for consistency
