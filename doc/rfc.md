# MyTeams RFC Documentation

## Table of Contents
- [Introduction](#introduction)
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
- [Packet Structures](#packet-structures)
  - [Type Definitions](#type-definitions)

## Introduction
This document outlines the specification of the MyTeams.

## Features
The MyTeams RFC supports the following features:
- User authentication and management.
- Retrieval of user lists and details.
- Sending messages to specific users.
- Subscription to team events.
- Resource creation, listing, and information retrieval.

## Commands

Commands send by the client to the server are prefixed with a `/` character and they end with the CRLF (`"/r/n"`) sequence.
The server wait for a string CRLF null-terminated, following the format of each commands.
Each command parameters must be between double quotes (\" \")

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
- Description: Set the command context to a team/channel/thread or none.
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

### SERVER KNOWN CODES:

```
  COMMAND_OK = 200
  HELP_MESSAGE = 201

  USERS_LIST = 211
  USER_INFO = 212
  USER_CREATED = 213
  USER_LOGGED_IN = 214
  USER_LOGGED_OUT = 215
  NEW_USER = 216

  MESSAGE_SENT = 220
  MESSAGE_RECEIVED = 221
  MESSAGES_LIST = 222
  THREAD_REPLY_RECEIVED = 223

  TEAM_SUBSCRIBED = 230
  TEAM_UNSUBSCRIBED = 231
  NO_SUBSCRIBED_TEAMS = 232

  TEAM_CREATED = 240
  CHANNEL_CREATED = 241
  THREAD_CREATED = 242
  REPLY_CREATED = 243

  TEAM_LIST = 250
  CHANNEL_LIST = 251
  THREAD_LIST = 252
  REPLY_LIST = 253

  CURRENT_USER_INFO = 260
  TEAM_INFO = 261
  CHANNEL_INFO = 262
  THREAD_INFO = 263

  GLOBAL_CONTEXT_SET = 270
  TEAM_CONTEXT_SET = 271
  CHANNEL_CONTEXT_SET = 272
  THREAD_CONTEXT_SET = 273
```

### SERVER KNOWN ERROR CODES

```
  SYNTAX_ERROR = 500
  SYNTAX_ERROR_IN_PARAMETERS = 501
  COMMAND_NOT_IMPLEMENTED = 502
  BAD_COMMAND_SEQUENCE = 503
  COMMAND_NOT_IMPLEMENTED_FOR_PARAMETER = 504
  NAME_TOO_LONG = 506
  DESCRIPTION_TOO_LONG = 507
  BODY_TOO_LONG = 508
  ALREADY_EXISTS = 509

  UNSUFFICIENT_PERMISSIONS = 510
  NOT_LOGGED_IN = 511
  USER_ALREADY_LOGGED_IN = 512
  ALREADY_LOGGED_IN = 513
  ALREADY_LOGGED_OUT = 514
  NOT_SUBSCRIBED = 515
  ALREADY_SUBSCRIBED = 516

  EMPTY_MESSAGE_LIST = 520

  EMPTY_TEAM_LIST = 551
  EMPTY_CHANNEL_LIST = 552
  EMPTY_THREAD_LIST = 553
  EMPTY_USER_LIST = 554
  EMPTY_REPLY_LIST = 555

  INEXISTANT_TEAM = 570
  INEXISTANT_CHANNEL = 571
  INEXISTANT_THREAD = 572
  INEXISTANT_USER = 573

  UNKNOWN_ERROR = 590
```

## Packet Structures

The server works by sending packets containing either null-terminated string or C-style structs, below are the ASCII tables representing the C-style structs used for sending and receiving packets in the server. Those struct are written in hexadecimal format directly into the socket.
Note that all strings should be null-terminated.
As some case doesn't need entire structures but only the previous user argument or a message, packet body may also contain a plain null-terminated string (like unknown team returning the given team uuid.).

List type commands will send each element of the list as a packet one by one.

To ensure the server is legit, the server will send a magic number written in 4 bytes before any packet.

### Type Definitions

#### `username_t` Type

A string representing a username, with a maximum length of 33 characters.

#### `title_t` Type

A string representing a title, with a maximum length of 33 characters.

#### `description_t` Type

A string representing a description, with a maximum length of 256 characters.

#### `body_t` Type

A string representing a body, with a maximum length of 513 characters.

### `uuid_t` Type

A string representing an C uiid generated by libuuid C library.

#### `packet_t` Struct
```c
+-------------------+--------------+-----------------+-------------------------+
| Field             | Type         | Size            | Description             |
+-------------------+--------------+-----------------+-------------------------+
| code              | int          | 4 bytes         | Reply code              |
| is_global         | bool         | 1 byte          | Global flag             |
| packet_type       | int          | 4 bytes         | Type of packet          |
| packet_body       | char[4096]   | 4096 bytes      | Body of the packet      |
+-------------------+--------------+-----------------+-------------------------+
```
The next given structures will be rawly written into the packet_t body.

There are multiple constants user in all structures to follow the same size.
```
MAX_NAME_LENGTH: 32 characters (bytes)
MAX_DESCRIPTION_LENGTH: 255 characters (bytes)
MAX_NAME_LENGTH: 512 characters (bytes)
```

#### `user_information_t` Struct
```c
+-------------------+------------------+---------------------+-----------------+
| Field             | Type             | Size                | Description     |
+-------------------+------------------+---------------------+-----------------+
| user_uuid         | uuid_t           | 16 bytes            | UUID of the user|
| username          | username_t       | MAX_NAME_LENGTH + 1 | Username        |
| is_logged         | bool             | 1 byte              | Logged-in status|
+-------------------+------------------+---------------------+-----------------+
```

#### `thread_t` Struct
```c
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
```c
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
```c
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
```c
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
```c
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
