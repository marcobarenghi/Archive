import click
from hexagons_lattice import HexagonLattice, validate_probability
"""
Example usage
Python 3.9.5
python generate_mono_bkg_lattice.py --x-dim 1920 --y-dim 1080 --hexagon-dim 20 --edge-width 1 --probability 0.5
                           --background-color black --edge-color white --central-color darkred --double-buffering --output lattice_1.png
"""

@click.command()
@click.option('--x-dim', default=1920, type=int, help="Width of the image in pixels")
@click.option('--y-dim', default=1080, type=int, help="Height of the image in pixels")
@click.option('--hexagon-dim', default=20, type=int, help="Radius of each hexagon")
@click.option('--edge-width', default=1, type=int, help="Width of the hexagons edges")
@click.option('--probability', default=1.0, type=float, callback=validate_probability, help="A probability value between (0;1]")
@click.option('--background-color', default='black', type=str, help="Background color of the image. String or hexadecimal")
@click.option('--edge-color', default='white', type=str, help="Edge color of the hexagons. String or hexadecimal")
@click.option('--central-color', default='red', type=str, help="Color of the central hexagon. String or hexadecimal")
@click.option('--double-buffering', type=bool, is_flag=True, default=False, help="Enable double buffering (default is False)"
                 "Artifacts might arise if hexagons are too small. Double buffering takes longer but gets rid of such artifacts")
@click.option('--output', default='lattice.png', type=str, help="Output file name")

def main(x_dim, y_dim, hexagon_dim, edge_width, probability ,background_color, edge_color, central_color, double_buffering, output):
    lattice = HexagonLattice(x_dim, y_dim, hexagon_dim, edge_width, probability,
                             background_color, edge_color, central_color, double_buffering, output)
    lattice.draw_lattice()

if __name__ == "__main__":
    main()
