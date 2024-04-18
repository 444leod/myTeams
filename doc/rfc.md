# MyTeams CLI RFC Documentation

## Table of Contents
- [Introduction](#introduction)
- [Usage](#usage)
- [Features](#features)
- [Commands](#commands)
  - [/help](#help)
  - [/login](#login)
  - [/logout](#logout)
  - [/users](#users)
  - [/user](#user)
  - [/send](#send)
  - [/messages](#messages)
  - [/subscribe](#subscribe)
  - [/subscribed](#subscribed)
  - [/unsubscribe](#unsubscribe)
  - [/use](#use)
  - [/create](#create)
  - [/list](#list)
  - [/info](#info)
- [Reply Code](#reply-code)

## Introduction
This document outlines the specification for the Command Line Interface (CLI) client of MyTeams.

## Usage
```
∼/B-NWP-400> ./myteams_cli –help
USAGE: ./myteams_cli ip port
```
- `ip`: The server IP address on which the server socket listens.
- `port`: The port number on which the server socket listens.

## Features
The MyTeams CLI client supports the following features:
- User authentication and management.
- Retrieval of user lists and details.
- Sending messages to specific users.
- Subscription to team events.
- Resource creation, listing, and information retrieval.

## Commands
### /help
- Description: Show help.

### /login
- Description: Set the username used by the client.
- Usage: `/login [“user_name”]`

### /logout
- Description: Disconnect the client from the server.

### /users
- Description: Get the list of all users that exist on the domain.

### /user
- Description: Get details about the requested user.
- Usage: `/user [“user_uuid”]`

### /send
- Description: Send a message to a specific user.
- Usage: `/send [“user_uuid”] [“message_body”]`

### /messages
- Description: List all messages exchanged with the specified user.
- Usage: `/messages [“user_uuid”]`

### /subscribe
- Description: Subscribe to the events of a team and its subdirectories.
- Usage: `/subscribe [“team_uuid”]`

### /subscribed
- Description: List all subscribed teams or list all users subscribed to a team.
- Usage: `/subscribed ?[“team_uuid”]`

### /unsubscribe
- Description: Unsubscribe from a team.
- Usage: `/unsubscribe [“team_uuid”]`

### /use
- Description: Set the command context to a team/channel/thread.
- Usage: `/use ?[“team_uuid”] ?[“channel_uuid”] ?[“thread_uuid”]`

### /create
- Description: Create a new resource based on the context.
- Usage:
  - `/create [“team_name”] [“team_description”]` (When the context is not defined)
  - `/create [“channel_name”] [“channel_description”]` (When `team_uuid` is defined)
  - `/create [“thread_title”] [“thread_message”]` (When `team_uuid` and `channel_uuid` are defined)
  - `/create [“comment_body”]` (When `team_uuid`, `channel_uuid`, and `thread_uuid` are defined)

### /list
- Description: List all existing resources based on the context.
- Usage:
  - `/list` (When the context is not defined)
  - `/list` (When `team_uuid` is defined)
  - `/list` (When `team_uuid` and `channel_uuid` are defined)
  - `/list` (When `team_uuid`, `channel_uuid`, and `thread_uuid` are defined)

### /info
- Description: Display details of the current resource based on the context.
- Usage:
  - `/info` (When the context is not defined)
  - `/info` (When `team_uuid` is defined)
  - `/info` (When `team_uuid` and `channel_uuid` are defined)
  - `/info` (When `team_uuid`, `channel_uuid`, and `thread_uuid` are defined)

## Reply Code

Reply codes indicate the status of a command execution. They follow a structured format:

- **2xx**: Positive Completion reply
- **5xx**: Permanent Negative Completion reply

These codes are further categorized based on their first digit:

- **x0x**: Global
- **x1x**: User related
- **x2x**: Message related
- **x3x**: Team (user-side) related
- **x4x**: Team (server-side) related
- **x5x**: List related
- **x6x**: Info related (no error)
- **x7x**: Context related
- **x90**: Unknown

The second code serves as the main context, but it may also be used in other contexts based on the packet type. It can specify an error that is not related to the context or may be used for two or three contexts.

The most important part of a response packet is the type of the packet, which can be one of the following:

- `NONE` = 0
- `ERROR` = 1
- `USER_INFORMATION` = 2
- `THREAD` = 3
- `TEAM` = 4
- `REPLY` = 5
- `CHANNEL` = 6
- `MESSAGE` = 7

## Packet Structures

The server works by sending packets containing C-style structs, below are the ASCII tables representing the C-style structs used for sending and receiving packets in the server. Those struct are written in hexadecimal format directly into the socket.
Note that all strings should be null-terminated.

#### `packet_t` Struct
```
+-------------------+--------------+-----------------+-------------------------+
| Field             | Type         | Size            | Description             |
+-------------------+--------------+-----------------+-------------------------+
| code              | int          | 4 bytes         | Reply code              |
| is_global         | bool         | 1 byte          | Global flag             |
| packet_type       | int          | 4 bytes         | Type of packet          |
| packet_body       | char[4096]   | 4096 bytes      | Body of the packet      |
+-------------------+--------------+-----------------+-------------------------+
```

#### `user_information_t` Struct
```
+-------------------+------------------+---------------------+-----------------+
| Field             | Type             | Size                | Description     |
+-------------------+------------------+---------------------+-----------------+
| user_uuid         | uuid_t           | 16 bytes            | UUID of the user|
| username          | username_t       | MAX_NAME_LENGTH + 1 | Username        |
| is_logged         | bool             | 1 byte              | Logged-in status|
+-------------------+------------------+---------------------+-----------------+
```

#### `thread_t` Struct
```
+-------------------+----------------------+---------------------+-------------------------+
| Field             | Type                 | Size                | Description             |
+-------------------+----------------------+---------------------+-------------------------+
| uuid              | uuid_t               | 16 bytes            | UUID of the thread      |
| creator_uuid      | uuid_t               | 16 bytes            | UUID of the creator     |
| timestamp         | time_t               | 8 bytes             | Creation timestamp      |
| title             | title_t              | MAX_NAME_LENGTH + 1 | Title of the thread     |
| body              | body_t               | MAX_BODY_LENGTH + 1 | Body of the thread      |
| channel_uuid      | uuid_t               | 16 bytes            | UUID of the channel     |
+-------------------+----------------------+---------------------+-------------------------+
```

#### `team_t` Struct
```
+-------------------+----------------------+---------------------+-------------------------+
| Field             | Type                 | Size                | Description             |
+-------------------+----------------------+---------------------+-------------------------+
| uuid              | uuid_t               | 16 bytes            | UUID of the team        |
| name              | title_t              | MAX_NAME_LENGTH + 1 | Name of the team        |
| description       | description_t        | MAX_DESC_LENGTH + 1 | Description of the team |
| creator_uuid      | uuid_t               | 16 bytes            | UUID of the creator     |
+-------------------+----------------------+---------------------+-------------------------+
```

#### `reply_t` Struct
```
+-------------------+----------------------+---------------------+-------------------------+
| Field             | Type                 | Size                | Description             |
+-------------------+----------------------+---------------------+-------------------------+
| uuid              | uuid_t               | 16 bytes            | UUID of the reply       |
| thread_uuid       | uuid_t               | 16 bytes            | UUID of the thread      |
| team_uuid         | uuid_t               | 16 bytes            | UUID of the team        |
| creator_uuid      | uuid_t               | 16 bytes            | UUID of the creator     |
| body              | body_t               | MAX_BODY_LENGTH + 1 | Body of the reply       |
| timestamp         | time_t               | 8 bytes             | Creation timestamp      |
+-------------------+----------------------+---------------------+-------------------------+
```

#### `channel_t` Struct
```
+-------------------+----------------------+---------------------+-------------------------+
| Field             | Type                 | Size                | Description             |
+-------------------+----------------------+---------------------+-------------------------+
| uuid              | uuid_t               | 16 bytes            | UUID of the channel     |
| name              | char[MAX_NAME_LENGTH+1] | MAX_NAME_LENGTH + 1 | Name of the channel     |
| description       | char[MAX_DESC_LENGTH+1] | MAX_DESC_LENGTH + 1 | Description of the channel |
| team_uuid         | uuid_t               | 16 bytes            | UUID of the team        |
+-------------------+----------------------+---------------------+-------------------------+
```

#### `message_t` Struct
```
+-------------------+----------------------+---------------------+-------------------------+
| Field             | Type                 | Size                | Description             |
+-------------------+----------------------+---------------------+-------------------------+
| uuid              | uuid_t               | 16 bytes            | UUID of the message     |
| sender_uuid       | uuid_t               | 16 bytes            | UUID of the sender      |
| receiver_uuid     | uuid_t               | 16 bytes            | UUID of the receiver    |
| timestamp         | time_t               | 8 bytes             | Creation timestamp      |
| body              | body_t               | MAX_BODY_LENGTH + 1 | Body of the message     |
+-------------------+----------------------+---------------------+-------------------------+
```