import math
from typing import List, Tuple, Optional
from PIL import Image, ImageDraw
import logging
import random
import click

logging.basicConfig(level=logging.DEBUG, format='%(asctime)s - %(levelname)s - %(message)s')

def validate_probability(ctx, param, value: float) -> float:
    """Validates probability between (0;1].

    Args:
        ctx, param: necessary for click options.
        value: Value parsed through click.

    Raises:
        click.BadParameter: Raises error if probability value is not between (0;1].
    
    Retuns:
        value, if validity check is passed.
    """
    if not (0 < value <= 1):
        raise click.BadParameter(f"Probability must be (0;1]. Value provided: {value}")
    return value

class HexagonLattice:
    def __init__(self, x_dim: int, y_dim: int, hexagon_dim: int, edge_width: int, probability: float,
                 background_color: Optional[str], edge_color: str, central_color: str, double_buffering: bool,
                 output: str, base_image_path: Optional[str] = None) -> None:
        """HexagonLattice class.

        Args:
            x_dim: Width of the image in pixels
            y_dim: Height of the image in pixels
            hexagon_dim: Radius of each hexagon
            edge_width: Width of the hexagon edges
            probability: Probability for each hexagon to be drawn.
            background_color: Background color of the image (None if using a base image)
            edge_color: Color of the hexagon edges
            central_color: Color of the central hexagon
            double_buffering: Flag to enable double buffering for smoother rendering and avoid artifacts
            output: Output file name
            base_image_path: Path to the base image to draw on, if provided
        """
        self.x_dim = x_dim
        self.y_dim = y_dim
        self.hexagon_dim = hexagon_dim
        self.edge_width = edge_width
        self.probability = probability
        self.background_color = background_color
        self.edge_color = edge_color
        self.central_color = central_color
        self.double_buffering = double_buffering
        self.output = output
        self.base_image_path = base_image_path

        if double_buffering:
            logging.warning("Using double buffer approach - runtime will greatly increase.")
        if not background_color and not base_image_path:
            raise ValueError("Either a background color or a base image must be provided.")

    def hexagon_vertices(self, center_x: int, center_y: int, size: int) -> List[Tuple[float, float]]:
        """Generate the vertices of a regular hexagon.
        
        Args:
            center_x: x coordinate of hexagon center
            center_y: x coordinate of hexagon center
            size: Hexagon radius

        Returns:
            list of coordinate of hexagon
        """
        return [
            (
                center_x + size * math.cos(math.pi / 3 * i),
                center_y + size * math.sin(math.pi / 3 * i),
            )
            for i in range(6)
        ]

    def draw_lattice(self) -> None:
        """Draw the hexagonal lattice."""
        logging.info("Starting to draw the lattice.")
        upscale_factor = 2 if self.double_buffering else 1
        buffer_x_dim = self.x_dim * upscale_factor
        buffer_y_dim = self.y_dim * upscale_factor

        # Load base image or create a new one
        if self.base_image_path:
            with Image.open(self.base_image_path) as base_img:
                base_img = base_img.convert("RGB").resize((buffer_x_dim, buffer_y_dim))
                buffer_image = base_img
        else:
            buffer_image = Image.new("RGB", (buffer_x_dim, buffer_y_dim), self.background_color)

        draw = ImageDraw.Draw(buffer_image)

        # Calculate hexagon dimensions
        hex_width = 1.5 * self.hexagon_dim * upscale_factor
        hex_height = math.sqrt(3) * self.hexagon_dim * upscale_factor
        cols = int(buffer_x_dim / hex_width) + 1
        rows = int(buffer_y_dim / hex_height) + 1

        # Center hexagon
        central_col = cols // 2
        central_row = rows // 2

        # Draw hexagons
        for row in range(rows):
            for col in range(cols):
                x = col * hex_width
                y = row * hex_height
                if col % 2 == 1:
                    y += hex_height / 2

                fill_color = self.central_color if (row == central_row and col == central_col) else None
                if not(row == central_row and col == central_col) and self.probability < 1.0:
                    r = random.uniform(0.0, 1.0)
                    if self.probability > r:
                        vertices = self.hexagon_vertices(x, y, self.hexagon_dim * upscale_factor)
                        draw.polygon(vertices, outline=self.edge_color, fill=fill_color, width=self.edge_width * upscale_factor)
                else:
                    vertices = self.hexagon_vertices(x, y, self.hexagon_dim * upscale_factor)
                    draw.polygon(vertices, outline=self.edge_color, fill=fill_color, width=self.edge_width * upscale_factor)

        # Downscale if double buffering is enabled
        if self.double_buffering:
            buffer_image = buffer_image.resize((self.x_dim, self.y_dim), Image.LANCZOS)

        buffer_image.save(self.output)
        logging.info(f"Lattice image saved as {self.output}")
