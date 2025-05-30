using Microsoft.EntityFrameworkCore;
using Microsoft.AspNetCore.Identity;
using NewsServiceApp.Models;

namespace NewsServiceApp.Data
{
    public static class SeedData
    {
        public static async Task EnsurePopulatedAsync(ApplicationDbContext db)
        {
            if (await db.Users.AnyAsync()) return;   // DB already seeded

            var hasher = new PasswordHasher<User>();

            var admin = new User
            {
                Username = "admin",
                IsAdmin = true
            };
            admin.PasswordHash = hasher.HashPassword(admin, "Admin123!");

            var guest = new User
            {
                Username = "guest",
                IsAdmin = false
            };
            guest.PasswordHash = hasher.HashPassword(guest, "Guest123!");

            db.Users.AddRange(admin, guest);
            await db.SaveChangesAsync();
        }
    }
}
