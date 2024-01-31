## Luca Andrei Fechete - Server Team

### Week 1:

This week, significant progress was made on the server component of our project. My efforts were primarily focused on two key areas:

1. **Structural Development Using CMake**: I successfully established the foundational structure of our project in the 'server' branch using CMake. This involved configuring CMakeLists.txt to ensure proper organization and modularization of the codebase, which is crucial for the project's scalability and maintainability.

2. **Implementation of Basic Server Functionality**: Leveraging the POCO C++ Libraries, I developed a basic server capable of handling client-to-client message transmission. This server is designed to efficiently process incoming requests from one client and relay these messages to another, demonstrating the fundamental networking capabilities that our project requires. This implementation showcases the potential of the POCO libraries in facilitating network programming and real-time communication.

For further reference and to aid in understanding the methodologies employed, the following resources can be consulted:
- POCO Libraries Repository: [POCO GitHub Repository](https://github.com/pocoproject/poco)
- POCO Documentation: [POCO Documentation](https://pocoproject.org/docs/)

These resources offer comprehensive information on the POCO library, including its modules, usage examples, and API documentation. They are instrumental for anyone looking to understand the underlying mechanics of our server's functionality.

### Week 2:
Building on the momentum from the first week, I further enhanced our server project with several key developments:

1. **Client Implementation Using Native Linux Headers**: This week, I focused on the client side of our project by creating a lightweight and efficient client using native Linux headers. This approach ensures compatibility and performance, leveraging the inherent capabilities of the Linux system for network communications. The client is designed to interact seamlessly with our server, providing a robust and responsive user experience.

2. **Account Creation Support**: Another major milestone was the implementation of account creation support. This feature enables users to create their own accounts, laying the groundwork for personalized and secure interactions within our network. The account creation process is integrated with the server's architecture, ensuring a seamless and user-friendly experience. This addition marks an important step towards a fully-featured and user-centric application.

These advancements collectively mark a significant progression in our project, showcasing the potential of our server-client architecture and setting a solid foundation for future enhancements and features.

### Week 3 and Week 4:

These weeks, I concentrated on detailed testing and debugging of both the server and client components in our system, focusing on enhancing performance, stability, and security. The server was scrutinized for its ability to handle multiple user requests simultaneously, ensuring optimal performance and data integrity. Client-side testing aimed at ensuring a glitch-free, responsive user interface across various devices and platforms.

Simultaneously, I advanced backend integration for our poker application, particularly by implementing the '/command number' feature. This addition allows players to execute game actions like 'bet', 'raise', or 'fold' via simple commands. Integrating this required a deep understanding of the game's mechanics and the technical aspects of real-time client-server communication. This week's efforts were geared towards refining user experience and laying a foundation for more complex features in our poker application.

### Week 5:

This week, I focused on the development of two crucial classes for a terminal-based poker game: the Dealer class and the Card class. The creation of these classes is a significant step towards simulating a functional poker game in a terminal environment.

1. **Dealer Class**: This class acts as the central controller of the game. It's responsible for managing the flow of the poker game, including shuffling and dealing cards, handling bets, and determining the winner of each hand. The Dealer class maintains the state of the game and enforces the rules, ensuring that the game progresses logically and fairly.

2. **Card Class**: The Card class represents the individual cards in a deck. Each instance of this class holds information about the card's suit (hearts, diamonds, clubs, spades) and rank (number or face). This class is fundamental to the game's operation, as it allows the creation and manipulation of a deck of cards, which is central to poker gameplay.

By testing these classes in a terminal, I'm ensuring that the basic functionalities – like card dealing, hand formation, and round progression – are working correctly. This setup provides a solid foundation for further development, such as integrating player interactions and merging the frontend with the client.

### Weeks 6 and 7:
Over the past few weeks, I have completed extensive testing and prepared the client component for integration into the backend and game logic of our poker application. This involved a thorough process of modularizing the code, enhancing its maintainability, scalability, and ease of use.

Modularization entailed breaking down the client's codebase into distinct, functional modules. Each module was designed to handle specific aspects of the client's operations, such as user input processing, game state management, and network communication. This approach not only streamlines the development process but also facilitates easier debugging and future enhancements, as changes can be made to individual modules without affecting the entire system.

The completion of testing ensured that all components function cohesively, with robust error handling and performance optimizations. This preparation paves the way for a seamless merger of the client with the backend, aligning it with the game logic to offer a comprehensive and efficient gaming experience.
