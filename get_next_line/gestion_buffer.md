```mermaid
stateDiagram-v2
    [*] --> BufferPhase
    
    state BufferPhase {
        [*] --> CheckContent
        
        state ReadProcess {
            [*] --> ReadBuffer
            ReadBuffer: bytes = read(fd, tmp, BUFFER_SIZE)
            ReadBuffer --> HandleRead
            
            HandleRead --> Process: bytes > 0
            HandleRead --> EOF: bytes == 0
            HandleRead --> Error: bytes < 0
            
            Process: tmp[bytes] = '\0'
            Process: Join avec content existant
        }
        
        CheckContent --> SearchNewline
        SearchNewline --> ReadProcess: No \n
        SearchNewline --> Extract: Found \n
    }

    note right of BufferPhase
        Points critiques:
        - Buffer stack
        - Gestion bytes lus
        - Join content
    end note
	```