# Address Book Management System

A console-based Address Book Management System developed in C for managing contact information efficiently.

## Overview

This project provides a simple and structured way to manage contacts through a command-line interface. It supports creating, searching, editing, deleting, listing, and saving contact records.

Contact data is stored in a CSV file so that records can be loaded and saved between program executions.

## Features

- Create new contacts
- Search contacts by name, phone number, or email
- Edit existing contact details
- Delete contacts with confirmation
- List all contacts
- Sort contacts alphabetically by name
- Input validation for name, phone number, and email
- Duplicate phone number prevention
- CSV file-based data storage
- Menu-driven console interface

## Technologies Used

- C Programming
- Structures
- Functions
- Pointers
- Strings
- Arrays
- File Handling
- CSV Data Storage

## Project Structure

```text
AddressBook/
│
├── main.c          # Main program and menu
├── contact.c       # Contact management functions
├── contact.h       # Contact declarations and structures
├── file.c          # File handling operations
├── file.h          # File handling declarations
├── telephone.csv   # Contact data storage
└── .gitignore      # Git ignore configuration
