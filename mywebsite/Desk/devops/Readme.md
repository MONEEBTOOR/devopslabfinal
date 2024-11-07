# Online Shopping Store Web Application

This is a simple online shopping store web application built with Flask, allowing users to view products, add them to a cart, and remove them as needed. This application is containerized using Docker for easy deployment.

## Project Structure


## Requirements

- [Docker](https://docs.docker.com/get-docker/) (for containerization)
- [Python 3.13](https://www.python.org/downloads/) (for development)

## Setup Instructions

### 1. Clone the Repository

Clone this repository to your local machine:

```bash
git clone <repository-url>
cd docker

##Ensure you have a Dockerfile in the project’s root directory with the following contents:

# Use a base image with Python
FROM python:3.13

# Set the working directory in the container
WORKDIR /app

# Copy the requirements file and install dependencies
COPY requirements.txt ./
RUN pip install --no-cache-dir -r requirements.txt

# Copy the rest of the application code
COPY . .

# Expose the port the app will run on
EXPOSE 5000

# Run the Flask app
CMD ["python", "app.py"]

##Use the following docker-compose.yml configuration to run the app with Docker Compose:

version: '3.8'

services:
  web:
    build: .
    ports:
      - "5000:5000"
    volumes:
      - .:/app
    command: python app.py


#Using Docker Compose
#To build and run the application with Docker Compose, execute the following commands in the terminal:

docker-compose up --build


#Without Docker Compose
#If you prefer not to use Docker Compose, you can build and run the Docker image manually:

###Build the Docker Image:

docker build -t shopping-store-app .

##Run the Docker Container:

docker run -p 5000:5000 shopping-store-app


##Accessing the Application
###Once the container is running, you can access the web application by navigating to:

http://127.0.0.1:5000

##Stopping the Application
##To stop the application, press CTRL + C in the terminal where the container is running. If you’re using Docker Compose, you can also use:

docker-compose down

######Technologies Used
Flask: Web framework for Python
Docker: Containerization platform

#####License
##This project is open-source and available under the MIT License.

This `README.md` file covers the basic setup, build, and run instructions, making it easy