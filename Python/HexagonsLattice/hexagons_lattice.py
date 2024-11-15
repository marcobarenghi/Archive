import click
import math
from PIL import Image, ImageDraw
from typing import List, Tuple
import logging

"""
Example usage
Python 3.9.5
python hexagons_lattice.py --x-dim 1920 --y-dim 1080 --hexagon-dim 20 --edge-width 1 
                           --background-color black --edge-color white --central-color darkred --output lattice_1.png
"""

logging.basicConfig(level=logging.DEBUG, format='%(asctime)s - %(levelname)s - %(message)s')

class HexagonLattice:
    def __init__(self, x_dim: int, y_dim: int, hexagon_dim: int, edge_width: int,
                 background_color: str, edge_color: str, central_color: str):
        """Initialize the HexagonLattice with dimensions and colors.

        Args:
            x_dim: width of the image in pixels
            y_dim: height of the image in pixels
            hexagon_dim: radius of each hexagon
            edge_width: width of the hexagon edges
            background_color: background color of the image
            edge_color: edge color of the hexagons
            central_color: color for the central hexagon
        """
        self.x_dim = x_dim
        self.y_dim = y_dim
        self.hexagon_dim = hexagon_dim
        self.edge_width = edge_width
        self.background_color = background_color
        self.edge_color = edge_color
        self.central_color = central_color

    def hexagon_vertices(self, center_x: int, center_y: int, size: int) -> List[Tuple[float, float]]:
        """Generate the vertices of a regular hexagon centered at (center_x, center_y).

        Args:
            center_x: x-coordinate of the center of the hexagon
            center_y: y-coordinate of the center of the hexagon
            size: radius (distance from the center to any vertex) of the hexagon

        Returns:
            list of (x, y) coordinates for each vertex of the hexagon
        """
        return [
            (
                center_x + size * math.cos(math.pi / 3 * i),
                center_y + size * math.sin(math.pi / 3 * i),
            )
            for i in range(6)
        ]

    def draw_lattice(self) -> Image:
        """Draw a lattice pattern with a central hexagon of a different color.

        Returns:
            PIL Image with the hexagons lattice pattern.
        """
        # Create a blank image
        image = Image.new("RGB", (self.x_dim, self.y_dim), self.background_color)
        draw = ImageDraw.Draw(image)

        # Calculate the distances between hexagon centers
        hex_width = 1.5 * self.hexagon_dim
        hex_height = math.sqrt(3) * self.hexagon_dim

        # Calculate number of rows and columns
        cols = int(self.x_dim / hex_width) + 1
        rows = int(self.y_dim / hex_height) + 1

        # Find the approximate central hexagon position
        central_col = cols // 2
        central_row = rows // 2

        for row in range(rows):
            for col in range(cols):
                # Calculate center of current hexagon and stagger odd columns
                x = col * hex_width
                y = row * hex_height
                if col % 2 == 1:
                    y += hex_height / 2

                # Set color for central hexagon
                fill_color = self.central_color if (row == central_row and col == central_col) else None

                # Draw
                vertices = self.hexagon_vertices(x, y, self.hexagon_dim)
                draw.polygon(vertices, outline=self.edge_color, fill=fill_color, width=self.edge_width)

        logging.info("Drawing lattice is done.")
        return image

@click.command()
@click.option('--x-dim', default=1920, help="Width of the image in pixels")
@click.option('--y-dim', default=1080, help="Height of the image in pixels")
@click.option('--hexagon-dim', default=20, help="Radius of each hexagon")
@click.option('--edge-width', default=1, help="Width of the hexagon edges")
@click.option('--background-color', default='black', help="Background color of the image")
@click.option('--edge-color', default='white', help="Edge color of the hexagons")
@click.option('--central-color', default='red', help="Color of the central hexagon")
@click.option('--output', default='lattice.png', help="Output file name")

def main(x_dim, y_dim, hexagon_dim, edge_width, background_color, edge_color, central_color, output):
    logging.info("Starting to draw lattice.")
    lattice = HexagonLattice(x_dim, y_dim, hexagon_dim, edge_width, background_color, edge_color, central_color)
    image = lattice.draw_lattice()
    logging.info("Ready to save output image.")
    image.save(output)
    logging.info(f"Lattice image saved as {output}")

if __name__ == "__main__":
    main()
