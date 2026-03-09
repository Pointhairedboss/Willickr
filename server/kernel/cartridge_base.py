from s1_midi import CC, Midi

class BaseCartridge:
    # Default mapping of ontology keys to S-1 CCs
    DEFAULT_MAPPING = {
        "afo:Loudness": CC.VOLUME,          # Intensity
        "afo:SpectralCentroid": CC.FILTER_CUTOFF, # Timbre
        "afo:ZeroCrossingRate": None,       # Density (handled in sequence logic)
        "afo:ModulationRate": CC.LFO_RATE,  # Motion
        "afo:RoomSize": CC.REVERB_LEVEL,    # Space
        "mo:Key": None                      # Key (handled in sequence logic)
    }

    def __init__(self):
        # Normalized values (0.0 to 1.0)
        self.ontology_values = {
            "afo:Loudness": 0.8,
            "afo:SpectralCentroid": 0.5,
            "afo:ModulationRate": 0.0,
            "afo:RoomSize": 0.2,
            "mo:Key": 60 # Un-normalized, MIDI root note
        }
        self.mapping = self.DEFAULT_MAPPING.copy()
        
    def apply_ontology(self, parameters: dict):
        """Update the values of the semantic ontology."""
        for k, v in parameters.items():
            if k in self.ontology_values:
                self.ontology_values[k] = v
                
    def get_cc(self, ontology_key: str) -> int:
        """Get the CC mapped to an ontology key."""
        return self.mapping.get(ontology_key)
        
    def get_val(self, ontology_key: str, min_val=0, max_val=127) -> int:
        """Convert a 0.0-1.0 float from the ontology state to a MIDI CC value."""
        v = self.ontology_values.get(ontology_key, 0.0)
        return int(min_val + (v * (max_val - min_val)))
        
    def execute(self, duration: float, device_id: int):
        raise NotImplementedError("Subclasses must implement execute()")
