import click
from hexagons_lattice import HexagonLattice, validate_probability
from PIL import Image
"""
Example usage
Python 3.9.5
python generate_png_lattice.py --input-image Path/To/Png.png --hexagon-dim 20 --edge-width 1 --probability 0.5
                          --edge-color white --double-buffering --output lattice_1.png
"""

@click.command()
@click.option('--input-image', required=True, type=str, help="Path to the input image")
@click.option('--hexagon-dim', default=20, type=int, help="Radius of each hexagon")
@click.option('--edge-width', default=1, type=int, help="Width of the hexagons edges")
@click.option('--probability', default=1.0, type=float, callback=validate_probability, help="A probability value between (0;1]")
@click.option('--edge-color', default='white', type=str, help="Edge color of the hexagons. String or hexadecimal")
@click.option('--double-buffering', type=bool, is_flag=True, default=False, help="Enable double buffering (default is False)"
                 "Artifacts might arise if hexagons are too small. Double buffering takes longer but gets rid of such artifacts")
@click.option('--output', default='lattice.png', type=str, help="Output file name")

def main(input_image, hexagon_dim, edge_width, probability, edge_color, double_buffering, output):
    # Use image size to set resolution
    with Image.open(input_image) as img:
        x_dim, y_dim = img.size
    
    lattice = HexagonLattice(x_dim, y_dim, hexagon_dim, edge_width, probability,
                            None, # No background color
                            edge_color, 
                            None, # No central Color
                            double_buffering, output, input_image
                            )
    lattice.draw_lattice()

if __name__ == "__main__":
    main()
