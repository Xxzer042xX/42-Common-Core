```mermaid
stateDiagram-v2
    [*] --> EntryPoint: get_next_line(fd)
    
    state ValidationPhase {
        [*] --> BasicChecks
        BasicChecks: - fd >= 0
        BasicChecks: - BUFFER_SIZE > 0
        BasicChecks --> ReadTest
        
        state ReadTest {
            [*] --> TestRead
            TestRead: read(fd, test, 0)
            TestRead --> ValidFD: read >= 0
            TestRead --> InvalidFD: read < 0
        }
    }

    EntryPoint --> ValidationPhase
    ValidationPhase --> NodePhase: ValidFD
    ValidationPhase --> [*]: InvalidFD
    NodePhase --> BufferPhase
    BufferPhase --> LinePhase
    LinePhase --> [*]: Return line

    note right of ValidationPhase
        Validation initiale:
        - Vérifie fd
        - Vérifie BUFFER_SIZE
        - Test read()
    end note
	```