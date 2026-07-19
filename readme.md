Orbit 🤖

Orbit is an ESP32-powered embedded systems project that brings together hardware control, web development, artificial intelligence,
and browser-based computer vision into a single interactive platform.

The ESP32 hosts its own web application, allowing users to wirelessly interact with connected hardware from any device on the same Wi-Fi network. 
Through this interface, users can control motors, monitor the system, and communicate with Orbit, an AI assistant powered by Google's Gemini API.

Unlike a typical chatbot, Orbit has its own custom personality and responds with short, humorous messages designed specifically for a 16×2 LCD display.
AI-generated responses are processed by the ESP32 and displayed directly on the hardware, creating an interactive embedded AI experience.

The project also explores computer vision from first principles. Instead of relying on OpenCV or pre-trained AI models, webcam frames are processed manually in JavaScript. 
Individual pixels are analyzed, selected colors are detected using RGB thresholding, centroids are calculated mathematically, and object movement is tracked in real time.
The resulting centroid can then be used to trigger hardware actions, demonstrating how browser-based computer vision can interact directly with embedded systems.

Orbit is designed as a long-term learning platform where new technologies can be added over time. 
The goal is not only to build interesting features but also to understand how they work internally by implementing them from the ground up whenever possible.
