import click
import math
from PIL import Image, ImageDraw
from typing import List, Tuple

"""
Example usage
Python 3.9.5
python hexagons_lattice.py --x-dim 1920 --y-dim 1080 --hexagon-dim 20 --edge-width 1 --background-color black --edge-color white --central-color darkred --output lattice_1.png
"""

def hexagon_vertices(center_x: int, center_y: int, size: int) -> List[Tuple[float, float]]:
    """ Generate the vertices of a regular hexagon centered at (center_x, center_y).

    Args
        center_x: x-coordinate of the center of the hexagon
        center_y: y-coordinate of the center of the hexagon
        size: radius (distance from the center to any vertex) of the hexagon

    Returns
        list of (x, y) coordinates for each vertex of the hexagon
    """
    return [
        (
            center_x + size * math.cos(math.pi / 3 * i),
            center_y + size * math.sin(math.pi / 3 * i),
        )
        for i in range(6)
    ]


def draw_lattice(x_dim: int, y_dim: int, hexagon_dim: int, edge_width: int, background_color, edge_color, central_color):
    """Draw a lattice pattern with a central hexagon of a different color.

    Arg
        x_dim: width of the image in pixels
        y_dim: height of the image in pixels
        hexagon_dim: radius of each hexagon
        edge_width: width of the hexagon edges
        background_color: background color of the image
        edge_color: edge color of the hexagons
        central_color: color for the central hexagon
    
    Returns
        PIL Image with the hexagons lattice pattern.
    """
    # Create a blank image
    image = Image.new("RGB", (x_dim, y_dim), background_color)
    draw = ImageDraw.Draw(image)

    # Calculate the distances between hexagon centers
    hex_width = 1.5 * hexagon_dim
    hex_height = math.sqrt(3) * hexagon_dim

    # Calculate number of rows and columns
    cols = int(x_dim / hex_width) + 1
    rows = int(y_dim / hex_height) + 1

    # Find the approximate central hexagon position
    central_col = cols // 2
    central_row = rows // 2

    for row in range(rows):
        for col in range(cols):
            # Calculate center of current hexagon and stagger odd columns
            # -> Important to avoid overlapping and produce hexagons lattice
            x = col * hex_width
            y = row * hex_height
            if col % 2 == 1:
                y += hex_height / 2

            # Set color for central hexagon
            fill_color = central_color if (row == central_row and col == central_col) else None

            # Draw
            vertices = hexagon_vertices(x, y, hexagon_dim)
            draw.polygon(vertices, outline=edge_color, fill=fill_color, width=edge_width)

    return image

# Click commands for CLI
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
    image = draw_lattice(x_dim, y_dim, hexagon_dim, edge_width, background_color, edge_color, central_color)
    image.save(output)
    print(f"Lattice image saved as {output}")

if __name__ == "__main__":
    main()
