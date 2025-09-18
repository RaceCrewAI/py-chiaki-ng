# Contributing to py-chiaki-ng

Thank you for your interest in contributing to py-chiaki-ng! This document provides guidelines for contributing to the project.

## Development Setup

1. **Fork and Clone**
   ```bash
   git clone https://github.com/yourusername/py-chiaki-ng.git
   cd py-chiaki-ng
   ```

2. **Install Development Dependencies**
   ```bash
   pip install -e ".[dev]"
   ```

3. **Install Pre-commit Hooks**
   ```bash
   pre-commit install
   ```

## Development Workflow

1. **Create a Feature Branch**
   ```bash
   git checkout -b feature/your-feature-name
   ```

2. **Make Your Changes**
   - Write code following our style guidelines
   - Add tests for new functionality
   - Update documentation as needed

3. **Run Tests**
   ```bash
   pytest
   pytest --cov=py_chiaki_ng  # With coverage
   ```

4. **Run Linting and Formatting**
   ```bash
   black py_chiaki_ng/
   flake8 py_chiaki_ng/
   mypy py_chiaki_ng/
   ```

5. **Commit Your Changes**
   ```bash
   git add .
   git commit -m "feat: add new feature description"
   ```

6. **Push and Create Pull Request**
   ```bash
   git push origin feature/your-feature-name
   ```

## Code Style

- **Python Style**: Follow PEP 8, enforced by `black` and `flake8`
- **Type Hints**: Use type hints for all functions and classes
- **Docstrings**: Use Google-style docstrings
- **Import Order**: Use `isort` for consistent import ordering

## Commit Messages

Follow [Conventional Commits](https://www.conventionalcommits.org/):

- `feat:` New feature
- `fix:` Bug fix
- `docs:` Documentation changes
- `style:` Code style changes (formatting, etc.)
- `refactor:` Code refactoring
- `test:` Adding or updating tests
- `chore:` Maintenance tasks

## Testing

- Write unit tests for all new functionality
- Maintain test coverage above 80%
- Test on multiple Python versions (3.8+)
- Include integration tests where appropriate

## Documentation

- Update README.md for user-facing changes
- Add docstrings to all public functions and classes
- Include examples in docstrings
- Update CHANGELOG.md following Keep a Changelog format

## Issues and Bug Reports

When reporting bugs, please include:

- Python version
- Operating system
- Steps to reproduce
- Expected vs actual behavior
- Relevant error messages

## Feature Requests

For feature requests:

- Describe the use case clearly
- Explain why it would be valuable
- Consider implementation complexity
- Provide examples if possible

## License

By contributing, you agree that your contributions will be licensed under the same license as the project (MIT License).
