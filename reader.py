import os 

PIPE_NAME = "my_pipe"

def main(): 
    # Wait for pipe to be created by writer
    print("Waiting for pipe to be created by writer...")
    while not os.path.exists(PIPE_NAME):
        import time
        time.sleep(0.1)
        
    print("Pipe found. Connecting to writer...")
    try: 
        with open(PIPE_NAME, "r") as pipe: 
            while True: 
                line = pipe.readline()
                if not line:
                    break
                print("Received:", line.strip())  # Print the received line
    except OSError as e:
        print(f"Failed to open or read from pipe: {e}")
    finally:
        # Don't remove the pipe - let writer handle cleanup
        print("Reader finished.")

if __name__ == "__main__":
    main()