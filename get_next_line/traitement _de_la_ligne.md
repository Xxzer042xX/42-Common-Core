```mermaid
stateDiagram-v2
    [*] --> LinePhase
    
    state LinePhase {
        [*] --> Extract
        
        state Extract {
            [*] --> FindLen
            FindLen: Cherche \n ou fin
            FindLen --> AllocLine
            
            AllocLine: malloc(len + 1)
            AllocLine --> CopyLine
            
            CopyLine: Copie jusqu'à \n
            CopyLine --> UpdateRest
        }
        
        state UpdateRest {
            [*] --> SaveRest
            SaveRest: Sauve après \n
            SaveRest --> Cleanup
            
            Cleanup: Free ancien content
        }
    }

    note right of LinePhase
        Points critiques:
        - Extraction précise
        - Malloc/Free correct
        - Update content
    end note
	```