 The provided code snippets are part of a larger set of functions that handle various aspects of SMB (Server Message Block) protocol operations. These functions are used to perform different tasks such as locking files, breaking file leases, and sending requests over the network. Below is an explanation of each function along with its purpose and key components:

1. **smb2_lockv Function:**
   - **Purpose:** This function sends a lock request for multiple locks (up to `num_lock`).
   - **Parameters:**
     - `xid`: Transaction identifier.
     - `tcon`: Connection handle to the server.
     - `persist_fid`: Persistent file ID.
     - `volatile_fid`: Volatile file ID.
     - `pid`: Process ID.
     - `num_lock`: Number of locks to be locked/unlocked.
     - `buf`: Buffer containing lock elements.
   - **Steps:**
     - Initialize a SMB2 lock request (`req`).
     - Set process ID and lock count in the request.
     - Prepare an I/O vector for sending the request.
     - Increment the RFC1002 length to account for the number of locks.
     - Send the request using `SendReceive2`.
     - Handle errors by incrementing failure statistics if a send error occurs.
   - **Return Value:** Returns an integer representing success or failure (0 on success, non-zero on failure).

2. **SMB2_lock Function:**
   - **Purpose:** This function encapsulates the functionality of `smb2_lockv` for a single lock request.
   - **Parameters:**
     - `xid`: Transaction identifier.
     - `tcon`: Connection handle to the server.
     - `persist_fid`: Persistent file ID.
     - `volatile_fid`: Volatile file ID.
     - `pid`: Process ID.
     - `length`: Length of the lock range.
     - `offset`: Offset within the file where the lock starts.
     - `lock_flags`: Flags indicating the type of lock (e.g., exclusive, shared).
     - `wait`: Boolean to indicate if the operation should wait for completion.
   - **Steps:**
     - Create a single lock element (`lock`).
     - Set its properties based on the provided parameters.
     - Call `smb2_lockv` with the created lock element and appropriate count (1).
   - **Return Value:** Returns an integer representing success or failure (0 on success, non-zero on failure).

3. **SMB2_lease_break Function:**
   - **Purpose:** This function sends a request to break a file lease.
   - **Parameters:**
     - `xid`: Transaction identifier.
     - `tcon`: Connection handle to the server.
     - `lease_key`: Lease key associated with the file.
     - `lease_state`: Current state of the lease.
   - **Steps:**
     - Initialize a SMB2 lease break request (`req`).
     - Set credit request and structure size in the request.
     - Copy the lease key into the request.
     - Send the request using `SendReceiveNoRsp`.
     - Handle errors by incrementing failure statistics if a send error occurs.
   - **Return Value:** Returns an integer representing success or failure (0 on success, non-zero on failure).

These functions are crucial for managing file locking and lease management in network file systems that support the SMB2 protocol. They abstract the low-level details of constructing and sending SMB2 requests, making it easier to perform higher-level operations like acquiring and releasing locks or breaking leases.