## Luca Andrei Fechete - Server Team

### Week 1:

This week, significant progress was made on the server component of our project. My efforts were primarily focused on two key areas:

1. **Structural Development Using CMake**: I successfully established the foundational structure of our project in the 'server' branch using CMake. This involved configuring CMakeLists.txt to ensure proper organization and modularization of the codebase, which is crucial for the project's scalability and maintainability.

2. **Implementation of Basic Server Functionality**: Leveraging the POCO C++ Libraries, I developed a basic server capable of handling client-to-client message transmission. This server is designed to efficiently process incoming requests from one client and relay these messages to another, demonstrating the fundamental networking capabilities that our project requires. This implementation showcases the potential of the POCO libraries in facilitating network programming and real-time communication.

For further reference and to aid in understanding the methodologies employed, the following resources can be consulted:
- POCO Libraries Repository: [POCO GitHub Repository](https://github.com/pocoproject/poco)
- POCO Documentation: [POCO Documentation](https://pocoproject.org/docs/)

These resources offer comprehensive information on the POCO library, including its modules, usage examples, and API documentation. They are instrumental for anyone looking to understand the underlying mechanics of our server's functionality.

## Week 2:
Building on the momentum from the first week, I further enhanced our server project with several key developments:

1. **Client Implementation Using Native Linux Headers**: This week, I focused on the client side of our project by creating a lightweight and efficient client using native Linux headers. This approach ensures compatibility and performance, leveraging the inherent capabilities of the Linux system for network communications. The client is designed to interact seamlessly with our server, providing a robust and responsive user experience.

2. **Server Enhancement with Multicasting Capabilities**: To improve the efficiency and scalability of our server, I implemented multicasting functionality. This allows the server to send messages to multiple clients simultaneously, significantly enhancing the communication process. This feature is particularly beneficial for scenarios requiring real-time updates or broadcasts to multiple clients, demonstrating our server's capacity to handle high-volume, simultaneous communications.

3. **Account Creation Support**: Another major milestone was the implementation of account creation support. This feature enables users to create their own accounts, laying the groundwork for personalized and secure interactions within our network. The account creation process is integrated with the server's architecture, ensuring a seamless and user-friendly experience. This addition marks an important step towards a fully-featured and user-centric application.

These advancements collectively mark a significant progression in our project, showcasing the potential of our server-client architecture and setting a solid foundation for future enhancements and features.
