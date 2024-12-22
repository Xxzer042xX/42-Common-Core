```mermaid
stateDiagram-v2
    [*] --> NodePhase
    
    state NodePhase {
        [*] --> FindNode
        FindNode --> CreateNode: Non trouvé
        FindNode --> UseNode: Trouvé
        
        state CreateNode {
            [*] --> Malloc
            Malloc: new = malloc(sizeof(t_list))
            Malloc --> Init: Success
            Malloc --> Error: Fail
            
            Init: new->fd = fd
            Init: new->content = NULL
            Init: new->next = storage
            Init --> UpdateStorage: storage = new
        }
    }

    note right of NodePhase
        Points critiques:
        - Une seule variable static
        - Gestion erreurs malloc
        - Chaînage correct
    end note
	```