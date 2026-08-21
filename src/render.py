
import os
import subprocess
from PIL import Image


def render(executable, ppm_path, png_path):
    """
    Run the RayTracer executable and convert its PPM output to PNG.

    Parameters
    ----------
    executable : str
        Path to the RayTracer executable.

    ppm_path : str
        Path where the generated PPM image will be saved.

    png_path : str
        Path where the converted PNG image will be saved.
    """

    executable = os.path.abspath(executable)
    ppm_path = os.path.abspath(ppm_path)
    png_path = os.path.abspath(png_path)

    # ---------------------------------------------------------
    # Validate executable
    # ---------------------------------------------------------

    if not os.path.isfile(executable):
        raise FileNotFoundError(
            f"RayTracer executable not found: {executable}"
        )

    if not os.access(executable, os.X_OK):
        raise PermissionError(
            f"RayTracer executable is not executable: {executable}"
        )

    # ---------------------------------------------------------
    # Create output directories
    # ---------------------------------------------------------

    ppm_dir = os.path.dirname(ppm_path)
    png_dir = os.path.dirname(png_path)

    if ppm_dir:
        os.makedirs(ppm_dir, exist_ok=True)

    if png_dir:
        os.makedirs(png_dir, exist_ok=True)

    # ---------------------------------------------------------
    # Run RayTracer
    # ---------------------------------------------------------

    print("Running RayTracer...")
    print(f"Executable: {executable}")

    with open(ppm_path, "wb") as ppm_file:

        result = subprocess.run(
            [executable],
            stdout=ppm_file,
            stderr=subprocess.PIPE
        )

    if result.returncode != 0:
        error = result.stderr.decode(errors="replace")

        raise RuntimeError(
            f"RayTracer execution failed:\n{error}"
        )

    print(f"PPM generated: {ppm_path}")

    # ---------------------------------------------------------
    # Convert PPM → PNG
    # ---------------------------------------------------------

    print("Converting PPM → PNG...")

    try:
        image = Image.open(ppm_path)
        image.save(png_path, "PNG")

    except Exception as error:
        raise RuntimeError(
            f"Failed to convert PPM to PNG: {error}"
        )

    print(f"PNG generated: {png_path}")

    return png_path

if __name__ == "__main__":
    render(
        "./sphere",
        "./image.ppm",
        "./sphere.png"
    )
