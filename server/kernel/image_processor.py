import numpy as np
from PIL import Image
import math
from typing import List, Dict, Tuple, Any

class ImageProcessor:
    def __init__(self):
        self.current_image: Image.Image = None
        self.image_data: np.ndarray = None
    
    def load_image(self, image_path: str, resize_to: Tuple[int, int] = (512, 512)):
        """Loads an image and prepares it for analysis."""
        try:
            img = Image.open(image_path).convert('RGB')
            if resize_to:
                img = img.resize(resize_to)
            self.current_image = img
            # Store as normalized float 0-1
            self.image_data = np.array(img) / 255.0 
            return {"status": "loaded", "size": img.size, "format": img.format}
        except Exception as e:
            return {"status": "error", "error": str(e)}

    def scanline(self, y_percent: float) -> Dict[str, List[float]]:
        """
        Scans a horizontal line at y_percent (0.0 to 1.0) of height.
        Returns brightness and hue arrays.
        """
        if self.current_image is None:
            raise ValueError("No image loaded")

        h, w, c = self.image_data.shape
        row_idx = int(y_percent * (h - 1))
        row_data = self.image_data[row_idx] # Shape (w, 3)

        # Calculate Brightness (Luminance)
        # Standard formula: 0.299R + 0.587G + 0.114B
        brightness = (0.299 * row_data[:, 0] + 0.587 * row_data[:, 1] + 0.114 * row_data[:, 2])

        # Calculate Saturation (approximation)
        # Max - Min
        saturation = np.max(row_data, axis=1) - np.min(row_data, axis=1)

        return {
            "brightness": brightness.tolist(),
            "saturation": saturation.tolist(),
            "red": row_data[:, 0].tolist(),
            "len": w
        }

    def grid_stats(self, grid_x: int, grid_y: int) -> List[Dict[str, float]]:
        """
        Divides image into a grid and returns stats for each cell.
        Useful for 'sequencer steps'.
        """
        if self.current_image is None:
            raise ValueError("No image loaded")
            
        h, w, _ = self.image_data.shape
        cell_h = h // grid_y
        cell_w = w // grid_x
        
        cells = []
        
        for y in range(grid_y):
            for x in range(grid_x):
                # Extract cell chunk
                y_start, y_end = y * cell_h, (y + 1) * cell_h
                x_start, x_end = x * cell_w, (x + 1) * cell_w
                chunk = self.image_data[y_start:y_end, x_start:x_end]
                
                # Averages
                avg_color = np.mean(chunk, axis=(0, 1))
                brightness = 0.299 * avg_color[0] + 0.587 * avg_color[1] + 0.114 * avg_color[2]
                
                cells.append({
                    "x": x, "y": y,
                    "r": float(avg_color[0]),
                    "g": float(avg_color[1]),
                    "b": float(avg_color[2]),
                    "brightness": float(brightness)
                })
        
        return cells

# Helper for testing
if __name__ == "__main__":
    print("ImageProcessor Lib")
    # processor = ImageProcessor()
    # print(processor.load_image("test.jpg"))
